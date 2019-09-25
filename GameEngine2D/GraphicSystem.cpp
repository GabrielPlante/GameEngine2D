#include "GraphicSystem.h"
#include "Console.h"

namespace ge {
	GraphicSystem::GraphicSystem(const int screenWidth, const int screenHeight)
		:window{ screenWidth, screenHeight }
	{
	}

	void GraphicSystem::update() {
		window.clear();

		//Update and render the console
		Console::getInstance()->update(window.getRenderer());
		Console::getInstance()->render(window.getRenderer());

		//Every other update goes here

		window.render();
	}
}
