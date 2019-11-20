#if !defined(__GPTBACKEND_REGISTRY_H)
#   define __GPTBACKEND_REGISTRY_H 1

char *regtype2str(uint8_t &regtype) {
	char *result = "UNKNOWN";

	if (12 < regtype) {
		result = "UNKNOWN";
	}

	return result;
}

struct registry_entry {
	char *keyname;
	char *valuename;
	uint8_t regtype;
	char *data;
};

struct registry {
};

#endif /* __GPTBACKEND_REGISTRY_H */

