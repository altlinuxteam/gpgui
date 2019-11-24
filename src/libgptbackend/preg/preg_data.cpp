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
#include "preg_data.h"
#include "config.h"

std::string preg::regtype2str(uint16_t &regtype) {
    std::string result = "UNKNOWN";

    switch (regtype) {
    case preg::REG_NONE: {
        result = "REG_NONE";
        break;
    }
    case preg::REG_SZ: {
        result = "REG_SZ";
        break;
    }
    case preg::REG_EXPAND_SZ: {
        result = "REG_EXPAND_SZ";
        break;
    }
    case preg::REG_BINARY: {
        result = "REG_BINARY";
        break;
    }
    case preg::REG_DWORD_LITTLE_ENDIAN: {
        result = "REG_DWORD_LITTLE_ENDIAN";
        break;
    }
    case preg::REG_DWORD_BIG_ENDIAN: {
        result = "REG_DWORD_BIG_ENDIAN";
        break;
    }
    case preg::REG_LINK: {
        result = "REG_LINK";
        break;
    }
    case preg::REG_MULTI_SZ: {
        result = "REG_MULTI_SZ";
        break;
    }
    case preg::REG_RESOURCE_LIST: {
        result = "REG_RESOURCE_LIST";
        break;
    }
    case preg::REG_FULL_RESOURCE_DESCRIPTOR: {
        result = "REG_FULL_RESOURCE_DESCRIPTOR";
        break;
    }
    case preg::REG_RESOURCE_REQUIREMENTS_LIST: {
        result = "REG_RESOURCE_REQUIREMENTS_LIST";
        break;
    }
    case preg::REG_QWORD: {
        result = "REG_QWORD";
        break;
    }
    case preg::REG_QWORD_LITTLE_ENDIAN: {
        result = "REG_QWORD_LITTLE_ENDIAN";
        break;
    }
    default: {
        result = "UNKNOWN";
        break;
    }
    } /* switch (regtype) */

    return result;
} /* std::string preg::regtype2str(uint16_t &regtype) */

uint16_t preg::str2regtype(std::string &regtype) {
    uint16_t result = 0;

    if ("REG_NONE" == regtype) {
        result = preg::REG_NONE;
    }
    if ("REG_SZ" == regtype) {
        result = preg::REG_SZ;
    }
    if ("REG_EXPAND_SZ" == regtype) {
        result = preg::REG_EXPAND_SZ;
    }
    if ("REG_BINARY" == regtype) {
        result = preg::REG_BINARY;
    }
    if ("REG_DWORD_LITTLE_ENDIAN" == regtype || "REG_DWORD" == regtype) {
        result = preg::REG_DWORD_LITTLE_ENDIAN;
    }
    if ("REG_DWORD_BIG_ENDIAN" == regtype) {
        result = preg::REG_DWORD_BIG_ENDIAN;
    }
    if ("REG_LINK" == regtype) {
        result = preg::REG_LINK;
    }
    if ("REG_MULTI_SZ" == regtype) {
        result = preg::REG_MULTI_SZ;
    }
    if ("REG_RESOURCE_LIST" == regtype) {
        result = preg::REG_RESOURCE_LIST;
    }
    if ("REG_FULL_RESOURCE_DESCRIPTOR" == regtype) {
        result = preg::REG_FULL_RESOURCE_DESCRIPTOR;
    }
    if ("REG_RESOURCE_REQUIREMENTS_LIST" == regtype) {
        result = preg::REG_RESOURCE_REQUIREMENTS_LIST;
    }
    if ("REG_QWORD" == regtype) {
        result = preg::REG_QWORD;
    }
    if ("REG_QWORD_LITTLE_ENDIAN" == regtype) {
        result = preg::REG_QWORD_LITTLE_ENDIAN;
    }

    return result;
} /* uint16_t preg::str2regtype(std::string &regtype) */
