#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Drawer.h"

#include "GameGraphicSystem.h"
#include "MessageOrigin.h"

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
		std::shared_ptr<GameGraphicSystem> gameGraphic{ new GameGraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT, &factoryFactory} };
		//Add the renderer to the drawer
		ge::Drawer::addRenderer(gameGraphic->getWindowRenderer());
		ge::Engine::getInstance()->addGraphicSystem(gameGraphic);

		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));

		//Create the texture to add to the entity
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{255, 0, 0, 255}) };
		SDL_Rect rect{ ge::Rectangle{0, 0, 50, 50}.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &rect);//Draw a simple rectangle
		SDL_Texture* texture = drawer.finishDrawing();

		//Add an entity
		//Create the entity
		GameEntity playerEntity{};

		playerEntity.setPosition(ge::Vector2<long> {200, 200});

		unsigned int id = factoryFactory.entityFactory.addComponent(std::move(playerEntity));

		RendererComponent rendererComponent;
		rendererComponent.owner = factoryFactory.entityFactory.getComponent(id);
		rendererComponent.size = ge::Vector2<int>{ 50, 50 };
		rendererComponent.texture = texture;
		factoryFactory.rendererComponentFactory.addComponent(std::move(rendererComponent));
	}

	GameCore::~GameCore() {
		ge::Engine::quit();
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
