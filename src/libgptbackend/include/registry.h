#if !defined(__GPTBACKEND_REGISTRY_H)
#   define __GPTBACKEND_REGISTRY_H 1

#include <stddef.h>

extern "C" {

const char *regtype2str(uint32_t &regtype);

struct registry_entry {
	char *keyname;
	char *valuename;
	uint32_t regtype;
	char *data;
};

}

#endif /* __GPTBACKEND_REGISTRY_H */

