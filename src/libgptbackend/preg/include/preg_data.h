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
#if !defined(__GPTBACKEND_PREG_DATA)
#define __GPTBACKEND_PREG_DATA 1

#include <cstddef>
#include <string>

namespace preg {

const uint16_t REG_NONE                       = 0;
const uint16_t REG_SZ                         = 1;
const uint16_t REG_EXPAND_SZ                  = 2;
const uint16_t REG_BINARY                     = 3;
const uint16_t REG_DWORD_LITTLE_ENDIAN        = 4;
const uint16_t REG_DWORD_BIG_ENDIAN           = 5;
const uint16_t REG_LINK                       = 6;
const uint16_t REG_MULTI_SZ                   = 7;
const uint16_t REG_RESOURCE_LIST              = 8;
const uint16_t REG_FULL_RESOURCE_DESCRIPTOR   = 9;
const uint16_t REG_RESOURCE_REQUIREMENTS_LIST = 10;
const uint16_t REG_QWORD                      = 11;
const uint16_t REG_QWORD_LITTLE_ENDIAN        = 12;

struct entry {
    std::string value_name;
    std::string key_name;
    uint16_t type;
    uint32_t size;
    uint16_t value;
};

/**
 * Convert PReg type value from DWORD into string representation. May
 * be useful when operating on PReg files from GUI.
 */
std::string regtype2str(uint16_t &regtype);

/**
 * Convert PReg type string representation into DWORD. May be useful
 * when serializing data.
 */
uint16_t str2regtype(std::string &regtype);

} /* namespace preg */

#endif /* __GPTBACKEND_PREG_DATA */
