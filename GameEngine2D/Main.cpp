#include <iostream>
#include "Engine.h"

int main() {
	Engine::init();
	Engine::getInstance()->mainLoop();
	return 0;
}