#include "Helpers.h"
#include <sstream>

const std::string Helpers::NUMBERS   = "0123456789";
const std::string Helpers::UPPERCASE = "ABCDEFGHIJKLMNOPQRTSUVWXYZ";
const std::string Helpers::LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
const std::string Helpers::SYMBOLS   = "!@#$%&*()-_=+,.<>;:~^][{}|";

const std::string Helpers::getRandom(int digits, int flags){
	std::string container;
	std::string random;

	if(flags&RAND_NUM){
		container.append(NUMBERS);
	}

	if(flags&RAND_UPPER){
		container.append(UPPERCASE);
	}

	if(flags&RAND_LOWER){
		container.append(LOWERCASE);
	}

	if(flags&RAND_SYMB){
		container.append(SYMBOLS);
	}

	std::stringstream stream;

	for(int i = 0; i < digits; i++){
		stream << container.at(rand()%container.length());
	}

	stream >> random;

	return random;
}