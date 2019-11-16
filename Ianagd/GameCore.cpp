#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"

#include "GameGraphicSystem.h"
#include "PhysicSystem.h"
#include "MessageOrigin.h"

#include "PhysicComponent.h"
#include "PositionComponent.h"

//Include the command
#include "CommandQuitConsole.h"

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ian {

	//Initialize the instance to nullptr
	GameCore* GameCore::instance{ nullptr };

	void GameCore::init() {
		if (!instance)
			instance = new GameCore{};
	}

	void GameCore::quit() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}

	GameCore::GameCore() {
		//Initialise the engine
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Create and add the graphic system to the engine
		std::shared_ptr<GameGraphicSystem> gameGraphic{ new GameGraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		ge::Engine::getInstance()->addGraphicSystem(gameGraphic);

		//Create and add the physic system to the engine
		std::shared_ptr<PhysicSystem> physicSystem{ new PhysicSystem{&factoryFactory.physicFactory} };
		physicSystem->subscribeTo(ge::Engine::getInstance());
		ge::Engine::getInstance()->addSystem(physicSystem);

		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));

		//Add an entity
		//Create the component
		PositionComponent positionComponent{};
		PhysicComponent physicComponent{ &positionComponent };
		//Create the entity
		ge::Entity playerEntity{};
		//Add the component to the entity
		playerEntity.addComponent(&positionComponent);
		playerEntity.addComponent(&physicComponent);
		//Add the component to their respective factory
		factoryFactory.positionFactory.addComponent(std::move(positionComponent));
		factoryFactory.physicFactory.addComponent(std::move(physicComponent));
		factoryFactory.entityFactory.addComponent(std::move(playerEntity));
	}

	GameCore::~GameCore() {
		ge::Engine::quit();
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
