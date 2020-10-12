#include "Core.h"
#undef main

#include <stdexcept>
#include <iostream>


int main() {

	try {
		ian::Core::init();

		ian::Core::getInstance()->run();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	//std::cin.get();

	return 0;
}