#include "preg_data.h"

std::string preg::regtype2str(uint32_t &regtype) {
	std::string result = "UNKNOWN";

	if (12 < regtype) {
		result = "UNKNOWN";
	}

	return result;
}

