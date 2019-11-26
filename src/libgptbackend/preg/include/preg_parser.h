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
#if !defined(__GPTBACKEND_PREG_PARSER)
#define __GPTBACKEND_PREG_PARSER 1

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "preg_data.h"

namespace preg {

/* This thing contains offsets for PReg file pointing to '[' and ']'
 * characters. This structure is internal to preg_parser. */
struct key_entry {
    size_t start_offset;
    size_t end_offset;
};

uint16_t buffer2uint16(const char *type_buffer);
uint32_t buffer2uint32(const char *type_buffer);
uint32_t parse_type(const char *type_buffer);

class preg_parser {
    std::ifstream polfile;
    std::string file_path;
    size_t raw_file_size = 0;
    char header[4];
    char version[4];
    size_t next_entry_start_offset = 10;

  public:
    preg_parser(std::string &file_path);
    entry get_next_entry();

  protected:
    void load_regpol(std::string &file_path);
    void read_header();
    void read_version();
    void check_header();
    void check_version();
    char read_byte(size_t abs_file_start_offset);
    std::string read_buf(size_t start_pos, size_t end_pos);
    size_t seek_next_separator(size_t abs_file_start_offset);
};

} /* namespace preg */

#endif /* __GPTBACKEND_PREG_PARSER */
