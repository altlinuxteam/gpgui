/*
Copyright (c) 2019 Igor Chudov <nir@sarfsc.ru>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of the Igor Chudov nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "preg_parser.h"
#include "config.h"
#include "iconv_wrapper.h"

uint16_t preg::buffer2uint16(const char *type_buffer) {
    uint16_t num =
        static_cast<uint16_t>(static_cast<unsigned char>(type_buffer[1]) << 8 |
                              static_cast<unsigned char>(type_buffer[0]));
    return num;
}

uint32_t preg::buffer2uint32(const char *type_buffer) {
    uint32_t num =
        static_cast<uint32_t>(static_cast<unsigned char>(type_buffer[3]) << 24 |
                              static_cast<unsigned char>(type_buffer[2]) << 16 |
                              static_cast<unsigned char>(type_buffer[1]) << 8 |
                              static_cast<unsigned char>(type_buffer[0]));
    return num;
}
uint32_t preg::parse_type(const char *type_buffer) {
    return preg::buffer2uint32(type_buffer);
}

preg::preg_parser::preg_parser(std::string &file_path) {
    this->file_path = file_path;

    this->load_regpol(this->file_path);
}

void preg::preg_parser::load_regpol(std::string &file_path) {
    this->polfile.open(file_path,
                       std::ios::in | std::ios::binary | std::ios::ate);
    if (this->polfile.good()) {
        this->polfile.seekg(0, std::ios::end);       /* Go to the end of file */
        this->raw_file_size = this->polfile.tellg(); /* Get file length */

        this->polfile.seekg(0,
                            std::ios::beg); /* Set file position to beginning */

        this->read_header();
        this->read_version();
    }
}

void preg::preg_parser::read_header() {
    if (this->polfile.good() && 4 < this->raw_file_size) {
        this->polfile.seekg(0,
                            std::ios::beg); /* Set file position to beginning */
        this->polfile.read(this->header, 4); /* Read first 4 bytes */
    }
    this->check_header();
}

void preg::preg_parser::read_version() {
    if (this->polfile.good() && 8 < this->raw_file_size) {
        /* Read bytes 4-7 of the file */
        this->polfile.seekg(4, std::ios::beg);
        this->polfile.read(this->version, 4);
    }
    this->check_version();
}

void preg::preg_parser::check_header() {
    if ('P' == this->header[0] && 'R' == this->header[1] &&
        'e' == this->header[2] && 'g' == this->header[3]) {
    } else {
        throw preg::invalid_magic();
    }
}

void preg::preg_parser::check_version() {
    if (1 == this->version[0] && 0 == this->version[1] &&
        0 == this->version[2] && 0 == this->version[3]) {
    } else {
        throw preg::invalid_version();
    }
}

namespace {
bool is_range_start(char symbol) {
    if ('[' == symbol) {
        return true;
    }
    return false;
}

bool is_range_end(char symbol) {
    if (']' == symbol) {
        return true;
    }
    return false;
}

bool is_preg_entry_separator(char symbol) {
    if (';' == symbol) {
        return true;
    }
    return false;
}
} // namespace

char preg::preg_parser::read_byte(size_t abs_file_start_offset) {
    char symbol;
    if (abs_file_start_offset < this->raw_file_size) {
        this->polfile.seekg(abs_file_start_offset, std::ios::beg);
        this->polfile.read(&symbol, 1);
    }
    // FIXME: Else throw exception.
    return symbol;
}

size_t preg::preg_parser::seek_next_separator(size_t abs_file_start_offset) {
    size_t end_offset = abs_file_start_offset;
    if (abs_file_start_offset < this->raw_file_size) {
        char sym_buf;
        for (size_t abs_file_offset = abs_file_start_offset;
             abs_file_offset <= this->raw_file_size; abs_file_offset++) {
            sym_buf = this->read_byte(abs_file_offset);
            if (is_range_start(sym_buf) || is_preg_entry_separator(sym_buf) ||
                is_range_end(sym_buf) ||
                abs_file_offset == this->raw_file_size) {

                end_offset = abs_file_offset;
                break;
            }
        }
    } else {
        end_offset = this->raw_file_size;
    }
    return end_offset;
}

std::string preg::preg_parser::read_buf(size_t start_pos, size_t end_pos) {
    std::cout << "Reading range from " << start_pos << " to " << end_pos << std::endl;
    if (start_pos >= this->raw_file_size) {
        throw preg::no_more_entries();
    }
    size_t entry_size = end_pos - start_pos;
    if ((start_pos + entry_size) > this->raw_file_size) {
        entry_size = raw_file_size - start_pos;
    }
    char *entry_buffer = new char[entry_size];
    this->polfile.seekg(start_pos);
    this->polfile.read(entry_buffer, entry_size);
    std::string bufstring(entry_buffer, entry_size);
    return bufstring;
}

preg::entry preg::preg_parser::get_next_entry() {
    preg::key_entry entry;
    entry.start_offset = this->next_entry_start_offset;
    entry.end_offset = this->next_entry_start_offset;
    if (this->next_entry_start_offset >= this->raw_file_size) {
        throw preg::no_more_entries();
    }

    size_t valuename_end = this->seek_next_separator(this->next_entry_start_offset);
    size_t keyname_end = this->seek_next_separator(valuename_end + 1);
    size_t type_end = this->seek_next_separator(keyname_end + 1);
    size_t size_end = this->seek_next_separator(type_end + 1);
    std::cout << "Starting at " << this->next_entry_start_offset
              << " and the key name ends at "
              << keyname_end
              << " value ends at: " << valuename_end
              << " type ends at: " << type_end
              << " size ends at: " << size_end
              << std::endl;
    std::vector<std::string> single_entry;
    std::string str_valuename = this->read_buf(this->next_entry_start_offset, valuename_end);
    std::string str_keyname = this->read_buf(valuename_end + 2, keyname_end);
    std::string str_type = this->read_buf(keyname_end + 2, type_end - 1);
    std::string str_size = this->read_buf(type_end + 2, size_end - 1);
    size_t value_size = preg::buffer2uint32(str_size.c_str());
    std::string str_value = this->read_buf(size_end + 2, size_end + 2 + value_size);
    std::cout << " keyname " << str_keyname
     << " valname " << str_valuename
     << " type " << str_type
     << " size " << value_size
     << " value " << str_value
     << std::endl;
    this->next_entry_start_offset = size_end + 2 + value_size + 4;

    preg::entry appentry;
    /* We also need converter from UTF-16 to UTF-8 */
    gptbackend::iconv_wrapper iwrapper("UTF-16LE", "UTF-8");

    std::string vn = iwrapper.convert(str_valuename);
    std::string kn = iwrapper.convert(str_keyname);
    appentry.value_name = std::string(vn, 0, vn.length() - 1);
    appentry.key_name = std::string(kn, 0, kn.length() - 1);
    std::cout << "Value name " << appentry.value_name << std::endl;
    std::cout << "Key name " << appentry.key_name << std::endl;
    appentry.type = preg::parse_type(str_type.c_str());
    std::cout << "Type " << preg::regtype2str(appentry.type) << std::endl;
    appentry.size = preg::buffer2uint32(str_size.c_str());
    appentry.value = const_cast<char*>(str_value.c_str());
    std::cout << "Size " << appentry.size << std::endl;
    std::cout << "Value " << appentry.value << std::endl;

    return appentry;
}

