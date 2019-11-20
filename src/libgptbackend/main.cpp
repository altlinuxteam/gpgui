#include "registry.h"

#include "preg_data.h"

extern "C" {

const char *regtype2str(uint32_t &regtype) {
	return preg::regtype2str(regtype).c_str();
}

}

