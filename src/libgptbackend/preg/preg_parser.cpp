#include "preg_parser.h"
#include "iconv_wrapper.h"

preg::preg_parser::preg_parser(std::string file_path) {
	this->file_path = file_path;

	this->load_regpol(this->file_path);
}

void
preg::preg_parser::load_regpol(std::string& file_path) {
	this->polfile.open(file_path, std::ios::in|std::ios::binary|std::ios::ate);
	if (this->polfile.good()) {
	    this->polfile.seekg(0, std::ios::end); /* Go to the end of file */
	    this->raw_file_size = this->polfile.tellg(); /* Get file length */

	    this->polfile.seekg(0, std::ios::beg); /* Set file position to beginning */

            this->read_header();
            this->read_version();
        }
}

void
preg::preg_parser::read_header() {
	if (this->polfile.good() && 4 < this->raw_file_size) {
	    this->polfile.seekg(0, std::ios::beg); /* Set file position to beginning */
	    this->polfile.read(this->header, 4); /* Read first 4 bytes */
	}
	this->check_header();
}

void
preg::preg_parser::read_version() {
	if (this->polfile.good() && 8 < this->raw_file_size) {
		/* Read bytes 4-7 of the file */
		this->polfile.seekg(4, std::ios::beg);
		this->polfile.read(this->version, 4);
	}
	this->check_version();
}

void
preg::preg_parser::check_header() {
	if ('P' == this->header[0] && 'R' == this->header[1] && 'e' == this->header[2] && 'g' == this->header[3]) {
		std::cout << "Preg success" << std::endl;
	} else {
		std::cout << "Not a pregfile" << std::endl;
	}
}

void
preg::preg_parser::check_version() {
	if (1 == this->version[0] && 0 == this->version[1] && 0 == this->version[2] && 0 == this->version[3]) {
		std::cout << "Version correct" << std::endl;
	} else {
		std::cout << "Version incorrect" << std::endl;
	}
}

preg::key_entry
preg::preg_parser::get_next_key_entry() {
	preg::key_entry entry;
	entry.start_offset = this->next_entry_start_offset;
	entry.end_offset = this->next_entry_start_offset;
	/* Check if we're not at the end of file */
	if (this->next_entry_start_offset < this->raw_file_size) {
		this->polfile.seekg(this->next_entry_start_offset, std::ios::beg);
		char* range_init = new char[1];
		this->polfile.read(range_init, 1);
		/* Check that we're at the beginning of the entry we
		 * want to parse */
		if ('[' == *range_init) {
			std::cout << "Range start found" << std::endl;
			size_t range_end = this->next_entry_start_offset;
			char* sym_buf = new char[1];
			/* Read file byte by byte seeking for the end of entry */
			for (size_t offset = range_end + 1; offset <= this->raw_file_size; offset++) {
				this->polfile.seekg(offset, std::ios::beg);
				this->polfile.read(sym_buf, 1);
				/* Build and return the entry if we're found its end */
				if (']' == *sym_buf) {
					std::cout << "Found range end at position: " << offset << std::endl;
					entry.end_offset = offset;
					this->next_entry_start_offset = offset + 2;
					return entry;
				}
			}
		}
	} else {
		std::cout << "Can't parse anymore";
		return entry;
	}
}

preg::entry
preg::preg_parser::read_entry(preg::key_entry kentry) {
	preg::entry appentry;
	std::vector<std::string> results = this->split_entry(kentry);
	std::cout << "Elements in split entry: " << (int)results.size() << std::endl;

	/* We also need converter from UTF-16 to UTF-8 */
	gptbackend::iconv_wrapper iwrapper("UTF-16LE", "UTF-8");

	appentry.value_name = iwrapper.convert(results.at(0));
	appentry.key_name = std::string(results.at(1), 1, results.at(1).size() - 4);
	std::cout << "Valname " << appentry.value_name << std::endl;
	std::cout << "Keyname " << appentry.key_name << std::endl;
	std::cout << "Type " << results.at(2) << std::endl;
	std::cout << "Etc 1 " << results.at(3) << std::endl;
	/* Read type */
/*	appentry.type = static_cast<uint32_t>(entry_buffer[key_name_offset + 1]);
	std::cout << "The type is " << appentry.type << std::endl;
*/
	return appentry;
}

preg::entry
preg::preg_parser::get_next_entry() {
	return this->read_entry(this->get_next_key_entry());
}

std::vector<std::string>
preg::preg_parser::split_entry(preg::key_entry kentry) {
	size_t entry_size = kentry.end_offset - kentry.start_offset;
	char* entry_buffer = new char[entry_size];
	this->polfile.seekg(kentry.start_offset);
	this->polfile.read(entry_buffer, entry_size);
	std::string bufstring(entry_buffer, entry_size);

	std::vector<std::string> results;

	size_t offset = 1;
	for (size_t i = offset; i < entry_size; i++) {
		if (';' == entry_buffer[i]) {
			results.push_back(std::string(bufstring, (offset+1), i));
			offset = i;
		}
	}

	return results;
}

