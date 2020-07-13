#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "lexical_item.h"
#include "string_conversions.h"

namespace olex {

	struct token_item {
		std::string token;
		std::string value;
		int word = 0, line = 0;
		bool last_item = false;
		token_item(std::string _token, std::string _value, int c_word, int c_line) : token(_token), value(_value), word(c_word), line(c_line) {}
		token_item(std::string _token, char _value, int c_word, int c_line) : token(_token), word(c_word), line(c_line) {
			std::string s;
			s = _value;
			value = _value;
		}
		token_item() {}
	};

	class tokenizer {
	private:
		char _string_ident = '"';  // How you want to parse out a string, with what character I mean...
		//Current token index(see get_next_token)
		int c_token = 0;
		long c_line = 1;

		/*Default tokens!*/
		const std::string KEYWORD = "IDENTIFIER";
		const std::string LITERAL = "LITERAL";
		const std::string CONSTANT = "CONSTANT";
		/**/
		std::string _int_ident = "";
		std::string _float_ident = "";
		std::vector<token_item> tokenized;  // Data from tokenize_string
		std::vector<lexical_item> items;  // USER Defined tokens buffer
		std::fstream file;
	public:
		bool tokenize_string(std::string s);
		void tokenize_file(std::string filename);
		token_item get_next_token();

	private:
		std::string _parse_string(std::string& s);
		bool _type_checker(std::string& buffer, int& _word);
	public:
		tokenizer() {
			/*
			There are some API default defined tokens,
			below you see CONSTANT, which are booleans, integers or floats
			*/
			lexical_item _c(CONSTANT, 1, "");
			_c._register_parser([](std::string& s) {
				string_conversions sc;
				/*
				Check if the word are a boolean
				*/
				if (s == "true" || s == "false")
					return;
				/*
				Check if the word are a integer or float
				*/
				for (char c : s) {
					if (!sc.char_is_num(c) && c != '.') {
						s = "NULL";
						return;
					}
				}
			});
			register_item(_c);
		}
		void register_item(lexical_item li) { items.push_back(li); }
		void set_string_identifier(char c) { _string_ident = c; }
	};
}
