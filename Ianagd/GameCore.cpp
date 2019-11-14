#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"

#include "GameGraphicSystem.h"
#include "PhysicSystem.h"
#include "CreatePhysicComponent.h"
#include "MessageOrigin.h"

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

		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));

		//Add an entity
		ge::Entity playerEntity{};
		PhysicComponent physicComponent{};
		std::shared_ptr<CreatePhysicComponent> componentMessage{ new CreatePhysicComponent{gameCore, std::move(physicComponent), &playerEntity} };
		ge::Engine::getInstance()->publish(componentMessage);
		entityManager.addEntity(std::move(playerEntity));
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
