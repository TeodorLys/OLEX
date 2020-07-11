#include "lexical_item.h"
#include "_error_handler.h"

namespace olex {

	lexical_item::lexical_item(std::string token_name, flags f, int i_count, std::string f_ident, ...) {
		va_list list;
		va_start(list, f_ident);

		lexical_item_helper(token_name, f, i_count, f_ident, list);

		va_end(list);
	}

	lexical_item::lexical_item(std::string token_name, int i_count, std::string f_ident, ...) {
		va_list list;
		va_start(list, f_ident);

		lexical_item_helper(token_name, flags::NILL, i_count, f_ident, list);

		va_end(list);
	}

	void lexical_item::lexical_item_helper(std::string token_name, flags f, int i_count, std::string f_ident, va_list& list) {
		_f = f;
		_token = token_name;

		identifiers.push_back(f_ident);

		for (int a = 0; a < i_count - 1; a++) {
			identifiers.push_back(va_arg(list, const char*));
			if (f == flags::FORCE) {
				if (identifiers[identifiers.size() - 1].size() > 1) {
					_error_handler(_error_handler::type::WARNING, "Items with the flag \"FORCE\", cant be longer than 1 character, the flag will be ignored");
					_f = flags::NILL;
				}
			}
		}
	}

	bool lexical_item::check_type(std::string s) {
		if (parser != nullptr) {
			parser(s);
			if (s != "NULL")
				return true;
			else
				return false;
		}
		for (int a = 0; a < identifiers.size(); a++) {
			if (s == identifiers[a])
				return true;
		}
		return false;
	}

	//If type are contained inside a string but does not exactly match, throw error!(Inside the tokenizer function)
	bool lexical_item::check_error_type(std::string s) {
		if (s.size() <= 0)
			return false;
		for (int a = 0; a < identifiers.size(); a++) {
			if (s.find(identifiers[a]) != std::string::npos && identifiers[a].size() > 0) {
				if (s.find(identifiers[a]) == 0 || s.find(identifiers[a]) + identifiers[a].size() == s.size())
					return true;
			}
		}
		return false;
	}
}