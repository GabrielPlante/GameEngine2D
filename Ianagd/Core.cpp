#include "Core.h"

#include "../GameEngine2D/ScriptComponent.h"
#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Storage.h"
#include "../GameEngine2D/Engine.h"

#include "../Map/MapGenerator.h"
#include "../Map/PathFinder.h"

#include "MovementSystem.h"
#include "GameValues.h"

#include "EntityHandler.h"

#include <iostream>

constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ian {
	void fillCommandList() {
	}

	void fillSystem() {
		ge::Engine::getInstance()->addSystem(std::shared_ptr<ge::System>{new MovementSystem{}});
	}

	Core* Core::instance{ nullptr };

	void Core::init() { instance = new Core{}; }

	void Core::quit() {
		if (instance)
			delete instance;
	}

	Core::Core() {
		//Init the engine
		ge::Engine::init();

		//Fill the command list
		fillCommandList();

		//Add a graphic system
		//std::shared_ptr<GraphicSystem> graphicSystem{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		//gRenderer = graphicSystem->getWindowRenderer();

		//Generate the map and it's texture
		map::MapGenerator::generate(10, { 0, 80, 0 });

		//Add the texture to the graphic system
		//graphicSystem->addMapTexture(mapTexture);

		//ge::Engine::getInstance()->addGraphicSystem(std::move(graphicSystem));

		//Add the other systems
		fillSystem();

		ge::Entity playerId{ EntityHandler::createEntity({400, 400}, 200) };

		EXEC_ARGS("fps", { 60 });

		//Create the class that control the player
		class PlayerControl : public ge::Script {
		public: void onUpdate() override {
			}
		};

		playerId.addComponent<ge::ScriptComponent>().bindScript<PlayerControl>();
	}

	Core::~Core() {
		ge::Engine::quit();
	}

	void Core::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}

