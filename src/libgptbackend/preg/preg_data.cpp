#include "preg_data.h"

char *preg::regtype2str(uint32_t &regtype) {
	char *result = "UNKNOWN";

	if (12 < regtype) {
		result = "UNKNOWN";
	}

	return result;
}

