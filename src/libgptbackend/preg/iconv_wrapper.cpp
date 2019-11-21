#include "config.h"
#include "iconv_wrapper.h"
#include <errno.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <system_error>
#include <stdexcept>

gptbackend::iconv_wrapper::iconv_wrapper(std::string from_encoding, std::string to_encoding) {
	this->from_encoding = from_encoding;
	this->to_encoding = to_encoding;
	this->conv = iconv_open(this->from_encoding.c_str(), this->to_encoding.c_str());
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

std::string
gptbackend::iconv_wrapper::convert(std::string from) {
	std::cout << this->from_encoding << " encoded string:" << std::endl;
	for (size_t i = 0; i < from.length(); i++) {
		std::cout << "Symbol (" << from.c_str()[i] << ") code [" << (int)from.c_str()[i] << "] position " << i << std::endl;
	}

	/* std::string.c_str() always returns NULL-terminated string
	 * as said in specification, so we have to use strncpy to
	 * copy all contents.
	 * It's a bit fun because the length of returned string
	 * is still the length of full buffer contents. */
	size_t from_string_length = (from.length() + 1) * sizeof(char);
	std::cout << "From length " << from_string_length << std::endl;
	char rom_string[from_string_length];
	for (size_t i = 0; i <= from_string_length; i++) {
		rom_string[i] = from.c_str()[i];
		std::cout << "Copying [" << i << "] " << (int)from.c_str()[i] << std::endl;
	}
	char * from_string = rom_string;
	std::cout << "Converting from " << from_string << std::endl;

	char * result = new char[4096];
	char * result_pointer = result;
	size_t result_size = 4096 * sizeof(char);

/*#if defined(__FreeBSD__)
	size_t invalids = 0;
	size_t conversion_result = __iconv(this->conv,
			(char**)&from_string,
			&from_string_length,
			(char**)&result,
			&result_size,
			__ICONV_F_HIDE_INVALID,
			&invalids);
#else
#endif*/ /* __FreeBSD__ */
	//size_t conversion_result = iconv(this->conv, (char**)&from_string, &from_string_length, (char**)&result, &result_size);
	size_t conversion_result = iconv(this->conv, &from_string, &from_string_length, &result_pointer, &result_size);
	std::cout << "Converted " << conversion_result << " symbols" << std::endl;
/*#if defined(__FreeBSD__)
	std::cout << "Invalid conversions " << invalids << " symbols" << std::endl;
#endif*/
	this->check_conversion_error();
	std::string conv_result = std::string(result_pointer);
	std::cout << "Decoded string length: " << conv_result.length() << std::endl;
	delete [] result_pointer;

	std::cout << this->to_encoding << " decoded string:" << std::endl;
	for (size_t i = 0; i < conv_result.length(); i++) {
		std::cout << "Symbol (" << conv_result.c_str()[i] << ") code [" << (int)conv_result.c_str()[i] << "] position " << i << std::endl;
	}
	//return from;
	return conv_result;
}

std::string
gptbackend::iconv_wrapper::convert(char *from) {
	return std::string(from);
}

void
gptbackend::iconv_wrapper::check_conversion_error() {
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

