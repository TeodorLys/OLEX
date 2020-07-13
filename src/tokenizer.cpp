#include "tokenizer.h"
#include <filesystem>
#include "_error_handler.h"

namespace olex {

	bool tokenizer::tokenize_string(std::string s) {
		std::string buff;
		int _word = 0;
		for (int i = 0; i < s.size(); i++) {
			char c = s[i];
			if (c == _string_ident) {
				std::string s_buff;
				s_buff = s[i];  // Adds the " to the buffer(SEE _parse_string function!)
				i++;
				while (s[i] != _string_ident) {
					s_buff += s[i];
					i++;
				}
				s_buff += s[i];  // Adds the " to the end of buffer
				tokenized.push_back(token_item(LITERAL, _parse_string(s_buff), _word++, c_line));
			}
			else if (c == ' ') {
				if (_type_checker(buff, _word)) continue;
				else return false;
			}
			buff += c;
		}
		if (!_type_checker(buff, _word)) return false;
		return true;
	}

	void tokenizer::tokenize_file(std::string filename) {
		if (!std::filesystem::exists(filename)) {
			_error_handler(_error_handler::type::CRITICAL, "file did not exist!");
		}

		file.open(filename, std::fstream::in);

		if (!file.is_open()) {
			_error_handler(_error_handler::type::CRITICAL, "file could not be opened!");
		}
	}

	token_item tokenizer::get_next_token() {
		/*
		When you have requested until end of line, we load
		in the next one.
		We do this to prevent large memory usage, if the file
		are very big, we do not want to load all into memory.
		So we go line by line :)
		*/
		if (tokenized.size() == c_token) {
			tokenized.clear();
			std::string buffer;
			bool is_last = false;
			if (std::getline(file, buffer).eof())
				is_last = true;
			if (!tokenize_string(buffer)) {
				_error_handler(_error_handler::type::CRITICAL, "Current file line could not be tokenized!", c_line, c_token + 1);
			}
			c_line++; //Current line
			if (is_last)
				tokenized[tokenized.size() - 1].last_item = true;
			// Reset the current token index
			c_token = 0;
		}
		// Returns the next token and adds 1 to the counter.
		return tokenized[c_token++];
	}

	bool tokenizer::_type_checker(std::string& buffer, int& _word) {
		bool found = false;
		/*
		Loops though the user defined lexical identifiers, SEE lexical_item.h
		*/

		token_item t_buffer("UNALLOCATED", 'U', 0, 0);
		/*
		Checking the flag FORCE!
		*/
		for (int a = 0; a < items.size(); a++) {
			if (items[a].get_flags() == lexical_item::flags::FORCE) {
				if (items[a].check_type(buffer[0])) {
					tokenized.push_back(token_item(items[a].token_id(), buffer[0], _word++, c_line));
					buffer.erase(0, 1);
				}
				else if (items[a].check_type(buffer[buffer.size() - 1])) {
					t_buffer = token_item(items[a].token_id(), buffer[buffer.size() - 1], _word++, c_line);
					buffer.pop_back();
				}
			}
		}

		for (int a = 0; a < items.size(); a++) {

			if (items[a].check_type(buffer)) {
				tokenized.push_back(token_item(items[a].token_id(), buffer, _word++, c_line));
				if (t_buffer.token != "UNALLOCATED")
					tokenized.push_back(t_buffer);
				buffer = "";
				found = true;
				break;
			}
			else if (items[a].check_error_type(buffer)) {
				_error_handler(_error_handler::type::WARNING, buffer + " contained a keyword!", c_line, 0);
				return false;
			}
		}
		if (!found) {
			//An unknown item type, like variable names
			tokenized.push_back(token_item(KEYWORD, buffer, _word++, c_line));
			if (t_buffer.token != "UNALLOCATED")
				tokenized.push_back(t_buffer);
			buffer = "";
		}
		return true;
	}

	std::string tokenizer::_parse_string(std::string& s) {
		/*
		TODO: Add _error_handler to this!
		*/
		if (s[0] != _string_ident)
			return "ERROR: parameter did not start with a \"";
		else
			s.erase(0, 1);  // Removes the "

		// If the string has no end identifier
		if (s.find("\"") == std::string::npos)
			return std::string("ERROR: no ") + _string_ident + std::string(" was found in string!");

		std::string buff = "";

		/*
		All of this are unnecessary... butt better be extra cautious(Right?)
		*/

		for (char c : s) {
			if (c == _string_ident)
				break;
			buff += c;
		}

		s.erase(0, s.find("\"") + 1);

		return buff;
	}
}
