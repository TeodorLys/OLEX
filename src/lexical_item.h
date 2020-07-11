#pragma once
#include <string>
#include <cstdarg>
#include <vector>

namespace olex {

	class lexical_item {
	private:
		std::string _token;
		void(*parser)(std::string&) = nullptr;
	public:
		enum flags {
			NILL,
			FORCE // Parse these tokens at begining or end of words i.e. seperators, like ";"
		};
		std::vector<std::string> identifiers;
	private:
		flags _f;
	public:
		/*
			* token_name: What the token identifier are named, whe you tokenize string
			 this name can be used as a type check.
			* _flag: !See flags enum!
			* i_count: How many identifiers are used ex. if, else if, else
			* f_ident: A list of all identifiers see above...
			TODO: Make the token_name a numerical identifier
			TODO: Make it so flags can be combined(for now we only have "FORCE")
		*/
		lexical_item(std::string token_name, flags _flag, int i_count, std::string f_ident, ...);
		lexical_item(std::string token_name, int i_count, std::string f_ident, ...);
		/*
			Here you can register a special parser. With the string parameter you get
			the current word that were extracted. If you set the string to "NULL" the
			parser will return FALSE and the.
			*NOTE* this overwrites the default parser (check_type)
		*/
		void _register_parser(void(*_p)(std::string&)) { parser = _p; }
		bool check_type(std::string s);

		//If type are contained inside a string but does not exactly match, throw error!(Inside the tokenizer function)
		bool check_error_type(std::string s);

	private:
		void lexical_item_helper(std::string token_name, flags f, int i_count, std::string f_ident, va_list& list);


	public:
		/*
		TODO: MAKE THIS AN INT! Make it so the user have to define a enum structure
		*/
		std::string token_id() const {
			return _token;
		}

		flags get_flags() const {
			return _f;
		}

		bool check_type(char c) {
			std::string s;
			s = c;
			return check_type(s);
		}

	};
}