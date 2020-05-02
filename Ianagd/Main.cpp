#include "GameCore.h"
#undef main

#include <stdexcept>
#include <iostream>


int main() {

	try {
		ian::GameCore::init();

		ian::GameCore::getInstance()->run();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	//std::cin.get();

	return 0;
}