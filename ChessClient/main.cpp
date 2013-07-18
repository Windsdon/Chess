#include "ChessClient.h"
#include <iostream>


int main() {
	ChessClient client;

	client.start();

	std::cin.get();
	return 0;
}