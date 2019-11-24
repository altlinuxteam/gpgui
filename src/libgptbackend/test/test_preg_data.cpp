#include "config.h"
#include <catch2/catch.hpp>

#include "preg_data.h"

TEST_CASE("Convert 0 to REG_NONE", "[regtype2str]") {
    uint16_t regtype = 0;
    REQUIRE("REG_NONE" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 1 to REG_SZ", "[regtype2str]") {
    uint16_t regtype = 1;
    REQUIRE("REG_SZ" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 2 to REG_EXPAND_SZ", "[regtype2str]") {
    uint16_t regtype = 2;
    REQUIRE("REG_EXPAND_SZ" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 3 to REG_BINARY", "[regtype2str]") {
    uint16_t regtype = 3;
    REQUIRE("REG_BINARY" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 4 to REG_DWORD_LITTLE_ENDIAN", "[regtype2str]") {
    uint16_t regtype = 4;
    REQUIRE("REG_DWORD_LITTLE_ENDIAN" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 5 to REG_DWORD_BIG_ENDIAN", "[regtype2str]") {
    uint16_t regtype = 5;
    REQUIRE("REG_DWORD_BIG_ENDIAN" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 6 to REG_LINK", "[regtype2str]") {
    uint16_t regtype = 6;
    REQUIRE("REG_LINK" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 7 to REG_MULTI_SZ", "[regtype2str]") {
    uint16_t regtype = 7;
    REQUIRE("REG_MULTI_SZ" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 8 to REG_RESOURCE_LIST", "[regtype2str]") {
    uint16_t regtype = 8;
    REQUIRE("REG_RESOURCE_LIST" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 9 to REG_FULL_RESOURCE_DESCRIPTOR", "[regtype2str]") {
    uint16_t regtype = 9;
    REQUIRE("REG_FULL_RESOURCE_DESCRIPTOR" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 10 to REG_RESOURCE_REQUIREMENTS_LIST", "[regtype2str]") {
    uint16_t regtype = 10;
    REQUIRE("REG_RESOURCE_REQUIREMENTS_LIST" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 11 to REG_QWORD", "[regtype2str]") {
    uint16_t regtype = 11;
    REQUIRE("REG_QWORD" == preg::regtype2str(regtype));
}

TEST_CASE("Convert 12 to REG_QWORD_LITTLE_ENDIAN", "[regtype2str]") {
    uint16_t regtype = 12;
    REQUIRE("REG_QWORD_LITTLE_ENDIAN" == preg::regtype2str(regtype));
}

TEST_CASE("Convert REG_NONE to 0", "[str2regtype]") {
    const uint16_t regtype = 0;
    std::string regname = "REG_NONE";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_SZ to 1", "[str2regtype]") {
    const uint16_t regtype = 1;
    std::string regname = "REG_SZ";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_EXPAND_SZ to 2", "[str2regtype]") {
    const uint16_t regtype = 2;
    std::string regname = "REG_EXPAND_SZ";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_BINARY to 3", "[str2regtype]") {
    const uint16_t regtype = 3;
    std::string regname = "REG_BINARY";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_DWORD_LITTLE_ENDIAN to 4", "[str2regtype]") {
    const uint16_t regtype = 4;
    std::string regname = "REG_DWORD_LITTLE_ENDIAN";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_DWORD_BIG_ENDIAN to 5", "[str2regtype]") {
    const uint16_t regtype = 5;
    std::string regname = "REG_DWORD_BIG_ENDIAN";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_LINK to 6", "[str2regtype]") {
    const uint16_t regtype = 6;
    std::string regname = "REG_LINK";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_MULTI_SZ to 7", "[str2regtype]") {
    const uint16_t regtype = 7;
    std::string regname = "REG_MULTI_SZ";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_RESOURCE_LIST to 8", "[str2regtype]") {
    const uint16_t regtype = 8;
    std::string regname = "REG_RESOURCE_LIST";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_FULL_RESOURCE_DESCRIPTOR to 9", "[regtype2str]") {
    const uint16_t regtype = 9;
    std::string regname = "REG_FULL_RESOURCE_DESCRIPTOR";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_RESOURCE_REQUIREMENTS_LIST to 10", "[str2regtype]") {
    const uint16_t regtype = 10;
    std::string regname = "REG_RESOURCE_REQUIREMENTS_LIST";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_QWORD to 11", "[str2regtype]") {
    const uint16_t regtype = 11;
    std::string regname = "REG_QWORD";
    REQUIRE(preg::str2regtype(regname) == regtype);
}

TEST_CASE("Convert REG_QWORD_LITTLE_ENDIAN to 12", "[str2regtype]") {
    const uint16_t regtype = 12;
    std::string regname = "REG_QWORD_LITTLE_ENDIAN";
    REQUIRE(preg::str2regtype(regname) == regtype);
}
