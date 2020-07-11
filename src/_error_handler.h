#pragma once
#include <string>

namespace olex {

	class _error_handler {
	private:
		bool exit_on_critical = true;
	public:
		enum class type {
			CRITICAL,
			WARNING
		};

		_error_handler(type t, std::string s, int line = -1, int word = -1) {
			switch (t) {
			case type::CRITICAL:
				_call_critical_error(s, line, word);
				break;
			case type::WARNING:
				_call_warning_error(s, line, word);
				break;
			}
		}

	private:
		/*
		Critical meaning EXITING efter message are shown and acknowledged
		*/
		void _call_critical_error(std::string s, int line, int word);
		void _call_warning_error(std::string s, int line, int word);

	public:
		/*
		Default are TRUE
		*/
		void set_exit_on_critical(bool b) {
			exit_on_critical = b;
		}
	};
}