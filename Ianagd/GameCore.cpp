#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "GameGraphicSystem.h"

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ian {

	GameCore::GameCore() {
		//Initialise the engine
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Create and add the graphic system to the engine
		std::shared_ptr<GameGraphicSystem> gameGraphic{ new GameGraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		ge::Engine::getInstance()->addGraphicSystem(gameGraphic);
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
