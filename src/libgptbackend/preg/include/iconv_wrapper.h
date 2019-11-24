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
#if !defined(__GPTBACKEND_ICONV_WRAPPER)
#define __GPTBACKEND_ICONV_WRAPPER 1

#include <string>

#include <iconv.h>

namespace gptbackend {

/**
 * Wrapper for POSIX iconv functionality to ease the access from C++
 * and provide a convenient way to operate on std::string buffers.
 */
class iconv_wrapper {
    /* C++ reinterpret_cast<> and static_cast<> can't be used in
     * this case */
    const iconv_t invalid_open = (iconv_t)-1;

    /* Disable copy since iconv_t can't duplicate */
    iconv_wrapper(iconv_wrapper const &) = delete;
    iconv_wrapper &operator=(iconv_wrapper const &) = delete;

    iconv_t conv;
    std::string from_encoding;
    std::string to_encoding;

  public:
    iconv_wrapper(std::string from_encoding, std::string to_encoding);
    ~iconv_wrapper();

    /**
     * Convert std::string to another format.
     */
    std::string convert(std::string from);

  private:
    /**
     * Check if there were conversion errors.
     */
    void check_conversion_error();
}; /* class iconv_wrapper */

} /* namespace gptbackend */

#endif /* __GPTBACKEND_ICONV_WRAPPER */
