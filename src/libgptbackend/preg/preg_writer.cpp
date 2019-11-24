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
#include "config.h"
#include "preg_writer.h"
#include "iconv_wrapper.h"

preg::preg_writer::preg_writer(std::string &preg_file) {
    this->preg_file = std::ofstream(preg_file, std::ios::out | std::ios::binary);
    this->preg_file.write(this->preg_magic, 4);
    this->preg_file.write(this->preg_version, 4);
    // FIXME: Throw exception if not this->preg_file.good()
} /* preg::preg_writer::preg_writer() */

preg::preg_writer::~preg_writer() {
    this->close();
} /* preg::preg_writer::~preg_writer() */

void preg::preg_writer::close() {
    if (this->preg_file) {
        this->preg_file.close();
    }
} /* preg::preg_writer::close() */

void preg::preg_writer::add_entry(preg::entry &pentry) {
    char null_terminator[2]{ '\x00', '\x00' };
    char separator[2]{ ';', '\x00' };
    char range_start[2]{ '[', '\x00' };
    char range_end[2]{ ']', '\x00' };

    gptbackend::iconv_wrapper iw("UTF-8", "UTF-16LE");

    std::string conv_value_name = iw.convert(pentry.value_name);
    std::string conv_key_name = iw.convert(pentry.key_name);

    const char *value_name = conv_value_name.c_str();
    size_t value_name_size = conv_value_name.length() * sizeof(char);

    const char *key_name = conv_key_name.c_str();
    size_t key_name_size = conv_key_name.length() * sizeof(char);

    char type[2];
    type[0] = pentry.type & 0xFF;
    type[1] = pentry.type >> 8;

    // FIXME: Make streambuf out of data and then write it at once.
    this->preg_file.write(range_start, 2);
    this->preg_file.write(value_name, value_name_size);
    this->preg_file.write(null_terminator, 2);
    this->preg_file.write(separator, 2);
    this->preg_file.write(key_name, key_name_size);
    this->preg_file.write(null_terminator, 2);
    this->preg_file.write(separator, 2);
    this->preg_file.write(type, 2);
    this->preg_file.write(null_terminator, 2);
    this->preg_file.write(separator, 2);
    this->preg_file.write(range_end, 2);
} /* void preg::preg_writer::add_entry() */

