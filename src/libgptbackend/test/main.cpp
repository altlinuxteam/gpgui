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
#define CATCH_CONFIG_MAIN
#include "config.h"
#include <catch2/catch.hpp>

#include "iconv_wrapper.h"
#include "preg_parser.h"

#include <string>

TEST_CASE("It is possible to convert UTF-8 string to UTF-16LE",
          "[iconv_wrapper]") {
    std::string test_str_utf8 = "Software\\BaseALT\\Policies\\Control";
    std::string test_str_utf16le{
        'S',  '\x00', 'o',  '\x00', 'f', '\x00', 't',  '\x00', 'w', '\x00',
        'a',  '\x00', 'r',  '\x00', 'e', '\x00', '\\', '\x00', 'B', '\x00',
        'a',  '\x00', 's',  '\x00', 'e', '\x00', 'A',  '\x00', 'L', '\x00',
        'T',  '\x00', '\\', '\x00', 'P', '\x00', 'o',  '\x00', 'l', '\x00',
        'i',  '\x00', 'c',  '\x00', 'i', '\x00', 'e',  '\x00', 's', '\x00',
        '\\', '\x00', 'C',  '\x00', 'o', '\x00', 'n',  '\x00', 't', '\x00',
        'r',  '\x00', 'o',  '\x00', 'l', '\x00'};
    {
        gptbackend::iconv_wrapper iwrapper("UTF-8", "UTF-16LE");
        REQUIRE(test_str_utf16le == iwrapper.convert(test_str_utf8));
    }
}

TEST_CASE("It is possile to convert UTF-16LE string to UTF-8",
          "[iconv_wrapper]") {
    std::string test_str_utf8 = "Software\\BaseALT\\Policies\\Control";
    std::string test_str_utf16le{
        'S',  '\x00', 'o',  '\x00', 'f', '\x00', 't',  '\x00', 'w', '\x00',
        'a',  '\x00', 'r',  '\x00', 'e', '\x00', '\\', '\x00', 'B', '\x00',
        'a',  '\x00', 's',  '\x00', 'e', '\x00', 'A',  '\x00', 'L', '\x00',
        'T',  '\x00', '\\', '\x00', 'P', '\x00', 'o',  '\x00', 'l', '\x00',
        'i',  '\x00', 'c',  '\x00', 'i', '\x00', 'e',  '\x00', 's', '\x00',
        '\\', '\x00', 'C',  '\x00', 'o', '\x00', 'n',  '\x00', 't', '\x00',
        'r',  '\x00', 'o',  '\x00', 'l', '\x00'};
    {
        gptbackend::iconv_wrapper iwrapper2("UTF-16LE", "UTF-8");
        REQUIRE(test_str_utf8 == iwrapper2.convert(test_str_utf16le));
    }
}
