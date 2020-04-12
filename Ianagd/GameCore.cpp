#include "GameCore.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Drawer.h"

#include "GameGraphicSystem.h"
#include "MovementSystem.h"
#include "MessageOrigin.h"

//Include the command
#include "CommandQuitConsole.h"
#include "CommandZoom.h"
#include "CommandResetZoom.h"

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

	GameCore::GameCore()
		: camera{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }
	{
		//Initialise the engine
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Create and add the graphic system to the engine
		std::shared_ptr<GameGraphicSystem> gameGraphic{ new GameGraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT, &factoryFactory.rendererComponentFactory} };
		//Add the renderer to the drawer
		ge::Drawer::addRenderer(gameGraphic->getWindowRenderer());
		ge::Engine::getInstance()->addGraphicSystem(gameGraphic);

		//Add the other systems
		std::shared_ptr<MovementSystem> movementSystem{ new MovementSystem{&factoryFactory.movementComponentFactory} };
		ge::Engine::getInstance()->addSystem(movementSystem);

		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandZoom{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandResetZoom{}}));

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

		//Create his renderer component
		RendererComponent rendererComponent;
		rendererComponent.owner = factoryFactory.entityFactory.getComponent(id);
		rendererComponent.size = ge::Vector2<int>{ 50, 50 };
		rendererComponent.texture = texture;
		unsigned int idRComp = factoryFactory.rendererComponentFactory.addComponent(std::move(rendererComponent));
		factoryFactory.entityFactory.getComponent(id)->addComponent(factoryFactory.rendererComponentFactory.getComponent(idRComp));

		//Create his movement component
		MovementComponent movementComponent;
		movementComponent.owner = factoryFactory.entityFactory.getComponent(id);
		unsigned int idMComp = factoryFactory.movementComponentFactory.addComponent(std::move(movementComponent));
		factoryFactory.entityFactory.getComponent(id)->addComponent(factoryFactory.movementComponentFactory.getComponent(idMComp));

		//Create a bot
		GameEntity bot{};
		bot.setPosition(ge::Vector2<long> {600, 600});
		unsigned int idBot = factoryFactory.entityFactory.addComponent(std::move(bot));

		//Create the texture to add to the bot
		renderer = drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{ 0, 0, 255, 255 });
		SDL_RenderFillRect(renderer, &rect);//Draw a simple rectangle
		SDL_Texture* textureBot = drawer.finishDrawing();


		//Create his renderer component
		RendererComponent rendererComponentBot;
		rendererComponentBot.owner = factoryFactory.entityFactory.getComponent(idBot);
		rendererComponentBot.size = ge::Vector2<int>{ 50, 50 };
		rendererComponentBot.texture = textureBot;
		unsigned int idRCompBot = factoryFactory.rendererComponentFactory.addComponent(std::move(rendererComponentBot));
		factoryFactory.entityFactory.getComponent(idBot)->addComponent(factoryFactory.rendererComponentFactory.getComponent(idRCompBot));

	}

	GameCore::~GameCore() {
		ge::Engine::quit();
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
