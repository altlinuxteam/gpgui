#if !defined(__GPTBACKEND_REGISTRY_H)
#define __GPTBACKEND_REGISTRY_H 1

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char *regtype2str(uint32_t &regtype);

struct registry_entry {
    char *keyname;
    char *valuename;
    uint32_t regtype;
    char *data;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GPTBACKEND_REGISTRY_H */
