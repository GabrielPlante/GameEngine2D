#include <stdexcept>

#include "Engine.h"

#include "GraphicSystem.h"

#include <iostream>

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

int main() {
	try {
		Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);
		Engine::getInstance()->addGraphicSystem(std::shared_ptr<System>{new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT}});
		Engine::getInstance()->mainLoop();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}