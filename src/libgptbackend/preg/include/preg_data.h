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
