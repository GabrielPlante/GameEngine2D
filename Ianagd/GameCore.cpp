#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"

#include "GameGraphicSystem.h"
#include "PhysicSystem.h"

//Include the command
#include "CommandQuitConsole.h"

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

		//Create and add the physic system to the engine
		std::shared_ptr<PhysicSystem> physicSystem{ new PhysicSystem{} };
		physicSystem->subscribeTo(ge::Engine::getInstance());
		ge::Engine::getInstance()->addSystem(physicSystem);


		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
