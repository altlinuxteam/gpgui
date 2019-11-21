#include "iconv_wrapper.h"
#include "config.h"
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <system_error>

gptbackend::iconv_wrapper::iconv_wrapper(std::string from_encoding,
                                         std::string to_encoding) {
    this->from_encoding = from_encoding;
    this->to_encoding = to_encoding;
    this->conv =
        iconv_open(this->from_encoding.c_str(), this->to_encoding.c_str());
    if (this->invalid_open == this->conv) {
        throw std::system_error(errno, std::system_category());
    }
}

gptbackend::iconv_wrapper::~iconv_wrapper() {
    if (this->invalid_open != this->conv) {
        int result = iconv_close(this->conv);
        this->conv = this->invalid_open;
        if (0 != result) {
            std::cout << "Error on iconv_close " << errno << std::endl;
        }
    }
}

std::string gptbackend::iconv_wrapper::convert(std::string from) {
    /* std::string.c_str() always returns NULL-terminated string
     * as said in specification, so we have to use strncpy to
     * copy all contents.
     * It's a bit fun because the length of returned string
     * is still the length of full buffer contents. */
    /*char from_buffer[from.length()];
    for (size_t i = 0; i <= from.length(); i++) {
        from_buffer[i] = from.c_str()[i];
    }
    const char * input_string = (char *)from.c_str();
    size_t input_string_length = (from.length() + 1) * sizeof(char);
    std::cout << "Converting string " << from << std::endl;
    std::cout << "Converting char " << std::string(from_buffer) << std::endl;
    std::cout << "From length " << from.length() << std::endl;
    std::cout << "Input length " << input_string_length << std::endl;

    char * result = new char[4096];
    char * result_pointer = result;
    size_t result_length = 2048 * sizeof(char);
    std::cout << "Result length " << result_length << std::endl;

    size_t conversion_result = iconv(this->conv, (char**)&input_string, &input_string_length, (char**)&result, &result_length);
    this->check_conversion_error();

    std::string res = std::string(result_pointer);
    std::cout << "Converted " << res << std::endl;
*/
    return from;
    //return res;
}

std::string gptbackend::iconv_wrapper::convert(char *from) {
    return std::string(from);
}

void gptbackend::iconv_wrapper::check_conversion_error() {
    switch (errno) {
    case EBADF: {
        std::cout << "EBADF" << std::endl;
        break;
    }
    case E2BIG: {
        std::cout << "E2BIG" << std::endl;
        break;
    }
    case EILSEQ: {
        std::cout << "EILSEQ" << std::endl;
        break;
    }
    case EINVAL: {
        std::cout << "EINVAL" << std::endl;
        break;
    }
    default: {
        std::cout << "Unknown error " << errno << std::endl;
        break;
    }
    }
}
