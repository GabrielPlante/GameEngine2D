#include <stdexcept>

#include "Engine.h"

#include <iostream>

int main() {
	try {
		Engine::init();
		Engine::getInstance()->mainLoop();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}