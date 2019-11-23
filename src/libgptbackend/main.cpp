#include "registry.h"

#include "preg_data.h"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char *regtype2str(uint16_t &regtype) {
    return preg::regtype2str(regtype).c_str();
}

uint16_t str2regtype(const char *regtype) {
    std::string reg_name(regtype);
    return preg::str2regtype(reg_name);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
