#include "_error_handler.h"
#include <iostream>

namespace olex {

	void _error_handler::_call_critical_error(std::string s, int line, int word) {
		std::string buffer = s;
		if (line != -1)
			buffer += " line: " + std::to_string(line);
		if (word != -1)
			buffer += " word: " + std::to_string(word);

		printf("[CRITICAL]: %s\n", buffer.c_str());
		if (exit_on_critical) {
			printf("ERROR WAS CRITICAL, PRESS ANY BUTTON TO EXIT!");
			std::cin.get();
			exit(0);
		}
	}

	void _error_handler::_call_warning_error(std::string s, int line, int word) {
		std::string buffer = s;
		if (line != -1)
			buffer += " line: " + std::to_string(line);
		if (word != -1)
			buffer += " word: " + std::to_string(word);

		printf("[WARNING]: %s\n", buffer.c_str());
	}
}