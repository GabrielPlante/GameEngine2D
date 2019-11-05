#include "GameGraphicSystem.h"

#include "../GameEngine2D/Console.h"

namespace ian {
	GameGraphicSystem::GameGraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{

	}

	void GameGraphicSystem::update() {
		window.clear();

		//Update and render the console
		ge::Console::getInstance()->update(window.getRenderer());
		//The console doesn't show itself automaticaly if it's not open
		ge::Console::getInstance()->render(window.getRenderer());

		//Every other update goes here

		window.render();
	}

}
