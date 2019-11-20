#if !defined(__GPTBACKEND_PREG_DATA)
#   define __GPTBACKEND_PREG_DATA 1

#include <cstddef>
#include <string>

namespace preg {

struct entry {
    std::string value_name;
    std::string key_name;
    uint32_t type;
};

std::string regtype2str(uint32_t &regtype);

} /* namespace preg */

#endif /* __GPTBACKEND_PREG_DATA */

