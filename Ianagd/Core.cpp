#include "Core.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Storage.h"
#include "../GameEngine2D/Engine.h"

#include "../Map/MapGenerator.h"
#include "../Map/PathFinder.h"

#include "CommandQuitConsole.h"

#include "MovementSystem.h"
#include "GraphicSystem.h"
#include "GameValues.h"

#include "EntityHandler.h"

#include <iostream>

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ian {
	void fillCommandList() {
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
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
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Fill the command list
		fillCommandList();


		//Add a graphic system
		std::shared_ptr<GraphicSystem> graphicSystem{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		gRenderer = graphicSystem->getWindowRenderer();

		//Generate the map and it's texture
		map::MapGenerator::generate(10, { 0, 80, 0 });
		ge::TextureWrapper mapTexture{ map::MapGenerator::generateTexture(gv::tileSize, {SCREEN_WIDTH, SCREEN_HEIGHT}) };

		//Add the texture to the graphic system
		graphicSystem->addMapTexture(mapTexture);

		ge::Engine::getInstance()->addGraphicSystem(std::move(graphicSystem));

		//Add the other systems
		fillSystem();

		//Quit the console and reduce fps to reduce work load
		EXEC("quitconsole");
		EXEC_ARGS("fps", { 60 });

		unsigned int playerId{ EntityHandler::createEntity({400, 400}, 200) };

		EntityHandler::setDestination(playerId, { 600, 600 });
	}

	void Core::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}

