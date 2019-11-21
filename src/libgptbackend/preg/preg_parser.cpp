#include "preg_parser.h"
#include "iconv_wrapper.h"


uint16_t
preg::buffer2uint16(const char * type_buffer) {
	uint16_t num = static_cast<uint16_t>(
		static_cast<unsigned char>(type_buffer[1]) << 8 |
		static_cast<unsigned char>(type_buffer[0])
	);
	return num;
}

uint32_t
preg::buffer2uint32(const char * type_buffer) {
	uint32_t num = static_cast<uint32_t>(
		static_cast<unsigned char>(type_buffer[3]) << 24 |
		static_cast<unsigned char>(type_buffer[2]) << 16 |
		static_cast<unsigned char>(type_buffer[1]) << 8 |
		static_cast<unsigned char>(type_buffer[0])
	);
	return num;
}
uint16_t
preg::parse_type(const char * type_buffer) {
	return preg::buffer2uint16(type_buffer);
}

preg::preg_parser::preg_parser(std::string file_path) {
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
        std::cout << "Preg success" << std::endl;
    } else {
        std::cout << "Not a pregfile" << std::endl;
    }
}

void preg::preg_parser::check_version() {
    if (1 == this->version[0] && 0 == this->version[1] &&
        0 == this->version[2] && 0 == this->version[3]) {
        std::cout << "Version correct" << std::endl;
    } else {
        std::cout << "Version incorrect" << std::endl;
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
}

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
        for (size_t abs_file_offset = abs_file_start_offset; abs_file_offset <= this->raw_file_size; abs_file_offset++) {
            sym_buf = this->read_byte(abs_file_offset);
            if (is_range_start(sym_buf) ||
                is_preg_entry_separator(sym_buf) ||
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

preg::key_entry preg::preg_parser::get_next_key_entry() {
    preg::key_entry entry;
    entry.start_offset = this->next_entry_start_offset;
    entry.end_offset = this->next_entry_start_offset;

    std::cout << "Starting at " << this->next_entry_start_offset << " and the next separator is at " << this->seek_next_separator(this->next_entry_start_offset) << std::endl;

    /* Check if we're not at the end of file */
    if (this->next_entry_start_offset < this->raw_file_size) {
        char range_init = this->read_byte(this->next_entry_start_offset);

        /* Check that we're at the beginning of the entry we
         * want to parse */
        if (is_range_start(range_init)) {
            std::cout << "Range start found at " << this->next_entry_start_offset << std::endl;
            char sym_buf;

            /* Read file byte by byte seeking for the end of entry */
            for (size_t offset = this->next_entry_start_offset + 1; offset <= this->raw_file_size;
                 offset++) {
                sym_buf = this->read_byte(offset);

                /* Build and return the entry if we're found its end */
                if (is_range_end(sym_buf)) {
                    std::cout << "Found range end at position: " << offset
                              << std::endl;
                    entry.end_offset = offset + 2;
                    this->next_entry_start_offset = offset + 2;
                    return entry;
                }
            }
        }
    } else {
        std::cout << "Can't parse anymore";
    }
    return entry;
}

preg::entry preg::preg_parser::read_entry(preg::key_entry kentry) {
    preg::entry appentry;
    std::vector<std::string> results = this->split_entry(kentry);
    std::cout << "Elements in split entry: " << (int)results.size()
              << std::endl;

    /* We also need converter from UTF-16 to UTF-8 */
    gptbackend::iconv_wrapper iwrapper("UTF-16LE", "UTF-8");

    appentry.value_name = iwrapper.convert(results.at(0));
    appentry.key_name = iwrapper.convert(results.at(1));
    std::cout << "Value name " << appentry.value_name << std::endl;
    std::cout << "Key name " << appentry.key_name << std::endl;
    appentry.type = preg::parse_type(results.at(2).c_str());
    std::cout << "Type " << preg::regtype2str(appentry.type) << std::endl;
    appentry.size = preg::buffer2uint32(results.at(3).c_str());
    appentry.value = preg::buffer2uint16(results.at(4).c_str());
    std::cout << "Size " << appentry.size << std::endl;
    std::cout << "Value " << appentry.value << std::endl;

    return appentry;
}

preg::entry preg::preg_parser::get_next_entry() {
    return this->read_entry(this->get_next_key_entry());
}

std::string preg::preg_parser::strip_square_braces(preg::key_entry kentry) {
    size_t entry_size = (kentry.end_offset-2) - (kentry.start_offset+2);
    char *entry_buffer = new char[entry_size];
    this->polfile.seekg((kentry.start_offset+2));
    this->polfile.read(entry_buffer, entry_size);
    std::string bufstring(entry_buffer, entry_size);
    return bufstring;
}

std::vector<std::string>
preg::preg_parser::split_entry(preg::key_entry kentry) {
    std::string bufstring = this->strip_square_braces(kentry);
    const char *raw_buffer = bufstring.c_str();
    std::vector<std::string> results;

    size_t offset = 0;
    for (size_t i = 0; i <= bufstring.length(); i++) {
	//std::cout << "[" << i << "] = (" << (int)raw_buffer[i] << "] " << raw_buffer[i] << std::endl;
        if (is_preg_entry_separator(raw_buffer[i]) || i == bufstring.length()) {
            size_t split_length = i - offset;
            std::string buf = std::string(bufstring, offset, split_length);
            results.push_back(buf);
            offset = i + 2; // Skip separator
            /*if (is_range_end(raw_buffer[i]) || i == bufstring.length()) {
            break;
	    }*/
            i++;
        }
    }

    return results;
}
