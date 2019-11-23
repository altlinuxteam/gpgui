#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "config.h"

#include "iconv_wrapper.h"
#include "preg_parser.h"

#include <string>

TEST_CASE("It is possible to convert UTF-8 string to UTF-16LE", "[iconv_wrapper]") {
    std::string test_str_utf8 = "Software\\BaseALT\\Policies\\Control";
    std::string test_str_utf16le{
'S', '\x00', 'o',  '\x00', 'f',  '\x00', 't', '\x00', 'w',  '\x00', 'a', '\x00',
'r', '\x00', 'e',  '\x00', '\\', '\x00', 'B', '\x00', 'a',  '\x00', 's', '\x00',
'e', '\x00', 'A',  '\x00', 'L',  '\x00', 'T', '\x00', '\\', '\x00', 'P', '\x00',
'o', '\x00', 'l',  '\x00', 'i',  '\x00', 'c', '\x00', 'i',  '\x00', 'e', '\x00',
's', '\x00', '\\', '\x00', 'C',  '\x00', 'o', '\x00', 'n',  '\x00', 't', '\x00',
'r', '\x00', 'o',  '\x00', 'l',  '\x00'
    };
    gptbackend::iconv_wrapper iwrapper("UTF-8", "UTF-16LE");
    REQUIRE(test_str_utf16le == iwrapper.convert(test_str_utf8));
}

TEST_CASE("It is possile to convert UTF-16LE string to UTF-8", "[iconv_wrapper]") {
    std::string test_str_utf8 = "Software\\BaseALT\\Policies\\Control";
    std::string test_str_utf16le{
'S', '\x00', 'o',  '\x00', 'f',  '\x00', 't', '\x00', 'w',  '\x00', 'a', '\x00',
'r', '\x00', 'e',  '\x00', '\\', '\x00', 'B', '\x00', 'a',  '\x00', 's', '\x00',
'e', '\x00', 'A',  '\x00', 'L',  '\x00', 'T', '\x00', '\\', '\x00', 'P', '\x00',
'o', '\x00', 'l',  '\x00', 'i',  '\x00', 'c', '\x00', 'i',  '\x00', 'e', '\x00',
's', '\x00', '\\', '\x00', 'C',  '\x00', 'o', '\x00', 'n',  '\x00', 't', '\x00',
'r', '\x00', 'o',  '\x00', 'l',  '\x00'
    };
    gptbackend::iconv_wrapper iwrapper2("UTF-16LE", "UTF-8");
    REQUIRE(test_str_utf8 == iwrapper2.convert(test_str_utf16le));
}

