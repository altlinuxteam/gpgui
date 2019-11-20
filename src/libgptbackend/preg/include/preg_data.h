#if !defined(__GPTBACKEND_PREG_DATA)
#   define __GPTBACKEND_PREG_DATA 1

#include <cstddef>
#include <string>

namespace preg {

struct entry {
    uint32_t type;
};

std::string regtype2str(uint32_t &regtype);

} /* namespace preg */

#endif /* __GPTBACKEND_PREG_DATA */

