#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "config.h"

#include "iconv_wrapper.h"
#include "preg_parser.h"

#include <string>
#include <iostream>
#include <fstream>

TEST_CASE("It is possible to convert UTF-8 string to UTF-16LE", "[iconv_wrapper]") {
    std::string test_str_utf8 = "Software\\BaseALT\\Policies\\Control";
    std::string test_str_utf16le{ 'S', '\x00', 'o', '\x00', 'f', '\x00', 't', '\x00',
        'w', '\x00', 'a', '\x00', 'r', '\x00', 'e', '\x00' };
    gptbackend::iconv_wrapper iwrapper("UTF-8", "UTF-16LE");
    gptbackend::iconv_wrapper iwrapper2("UTF-16LE", "UTF-8");
    std::cout << "1 " << iwrapper.convert(test_str_utf8) << std::endl;
    std::cout << "2 " << iwrapper2.convert(test_str_utf16le) << std::endl;
    //CHECK(false);
}

TEST_CASE("Registry.pol can be parsed", "[preg]") {
    preg::preg_parser *test_regpol = new preg::preg_parser("Registry.pol");
    test_regpol->get_next_entry();
    test_regpol->get_next_entry();
    test_regpol->get_next_entry();
    test_regpol->get_next_entry();
}

