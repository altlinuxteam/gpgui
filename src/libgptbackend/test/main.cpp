#include "config.h"

#include "preg_parser.h"

#include <iostream>

int main(int argc, char **argv) {
	preg::preg_parser *test_regpol = new preg::preg_parser("Registry.pol");
	test_regpol->get_next_entry();
	test_regpol->get_next_entry();
	test_regpol->get_next_entry();
	test_regpol->get_next_entry();
	/*preg::key_entry entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;
	entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;
	entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;
	entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;
	entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;
	entry = test_regpol->get_next_key_entry();
	std::cout << "Entry start: " << entry.start_offset << std::endl;
	std::cout << "Entry end " << entry.end_offset << std::endl;*/
	return 0;
}

