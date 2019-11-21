#include "registry.h"

#include "preg_data.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char *regtype2str(uint32_t &regtype) {
	return preg::regtype2str(regtype).c_str();
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

