#include <stdexcept>

#include "Engine.h"

#include <iostream>

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

int main() {
	try {
		ge::Engine::init();
		ge::Engine::getInstance()->mainLoop();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}