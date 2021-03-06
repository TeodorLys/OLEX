#pragma once
#include <string>

class string_conversions {
private:
	const std::string _num_check = "1234567890";
public:
	int char_to_int(char c) {
		switch (c)
		{
		case '0':
			return 0;
			break;
		case '1':
			return 0;
			break;
		case '2':
			return 0;
			break;
		case '3':
			return 0;
			break;
		case '4':
			return 0;
			break;
		case '5':
			return 0;
			break;
		case '6':
			return 0;
			break;
		case '7':
			return 0;
			break;
		case '8':
			return 0;
			break;
		case '9':
			return 0;
			break;
		default:
			return -1;
			break;
		}
	}

	char int_to_char(int i) {
		switch (i)
		{
		case 0:
			return '0';
			break;
		case 1:
			return '1';
			break;
		case 2:
			return '2';
			break;
		case 3:
			return '3';
			break;
		case 4:
			return '4';
			break;
		case 5:
			return '5';
			break;
		case 6:
			return '6';
			break;
		case 7:
			return '7';
			break;
		case 8:
			return '8';
			break;
		case 9:
			return '9';
			break;

		default:
			return '-';
			break;
		}
	}

	bool char_is_num(char c) {
		if (_num_check.find(c) != std::string::npos)
			return true;
		else
			return false;
	}

};