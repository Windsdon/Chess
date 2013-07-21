#include "ChessClient.h"
#include <iostream>
#include <time.h>


int main() {
	srand(time(NULL));
	ChessClient client;

	client.start();

	std::cin.get();
	return 0;
}