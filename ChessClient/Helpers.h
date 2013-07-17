#ifndef HELPERS_H
#define HELPERS_H

#include <string>

class Helpers {
	public:
		static const std::string getRandom(int, int); 

		static const int RAND_NUM = 1;
		static const int RAND_UPPER = 2;
		static const int RAND_LOWER = 4;
		static const int RAND_SYMB = 8;

		static const std::string NUMBERS;
		static const std::string UPPERCASE;
		static const std::string LOWERCASE;
		static const std::string SYMBOLS;
};

#endif