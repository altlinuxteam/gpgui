#if !defined(__GPTBACKEND_PREG_PARSER)
#   define __GPTBACKEND_PREG_PARSER 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

#include "preg_data.h"

namespace preg {

/* This thing contains offsets for PReg file pointing to '[' and ']'
 * characters. This structure is internal to preg_parser. */
struct key_entry {
	size_t start_offset;
	size_t end_offset;
};

class preg_parser {
	std::ifstream polfile;
	std::string file_path;
	size_t raw_file_size = 0;
	char header[4];
	char version[4];
	size_t next_entry_start_offset = 8;
public:
	preg_parser(std::string file_path);
	entry get_next_entry();

private:
	void load_regpol(std::string& file_path);
	void read_header();
	void read_version();
	void check_header();
	void check_version();
	key_entry get_next_key_entry();
	entry read_entry(key_entry kentry);
	std::vector<std::string> split_entry(key_entry kentry);
};

} /* namespace preg */

#endif /* __GPTBACKEND_PREG_PARSER */
