#include "GameCore.h"
#include <SDL.h>

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Camera.h"
#include "../GameEngine2D/Drawer.h"

#include "GameGraphicSystem.h"
#include "MapRepresentation.h"
#include "FactoryFactory.h"
#include "MovementSystem.h"
#include "MessageOrigin.h"
#include "GameValues.h"
#include "MapSystem.h"

//Include the command
#include "CommandQuitConsole.h"
#include "CommandEntityInfo.h"
#include "CommandResetZoom.h"
#include "CommandZoom.h"

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ian {

	//Initialize the instance to nullptr
	GameCore* GameCore::instance{ nullptr };

	void GameCore::init() {
		if (!instance) {
			instance = new GameCore{};
			instance->setupGame();
		}
	}

	void GameCore::quit() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}

	void GameCore::setupGame() {

		//Create the texture to add to the entity
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{255, 0, 0, 255}) };
		SDL_Rect rect{ ge::Rectangle{0, 0, 50, 50}.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &rect);//Draw a simple rectangle
		SDL_Texture* texturePlayer = drawer.finishDrawing();

		//---Add an entity---
		//Create the entity with his component list: a position, a texture, a movement, and a collision
		playerId = factoryFactory->createEntity({ 0, 1, 4, 3 });

		unsigned int posCompIndex{ factoryFactory->getEntityCompId(playerId, positionCompId) };
		//Set his position
		factoryFactory->positionFactory.getComponent(posCompIndex)->position = { 200, 200 };

		//Set his renderer component
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(playerId, rendererCompId))->positionComponentId = posCompIndex;
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(playerId, rendererCompId))->size = { 50, 50 };
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(playerId, rendererCompId))->setTexture(texturePlayer);

		//Set his movement component
		factoryFactory->tileMovementFactory.getComponent(factoryFactory->getEntityCompId(playerId, tileMovementCompId))->positionComponentId = posCompIndex;

		//Set his collision component
		//factoryFactory.collisionFactory.getComponent(factoryFactory.getEntityCompId(playerId, collisionCompId))->size = 50;

		//Create a bot without a movement component
		unsigned int botId{ factoryFactory->createEntity(std::vector<int>{0, 1, 3}) };
		posCompIndex = factoryFactory->getEntityCompId(botId, positionCompId);
		factoryFactory->positionFactory.getComponent(posCompIndex)->position = { 600, 600 };

		//Create the texture to add to the bot
		renderer = drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{ 0, 0, 255, 255 });
		SDL_RenderFillRect(renderer, &rect);//Draw a simple rectangle
		SDL_Texture* textureBot = drawer.finishDrawing();


		//Set his renderer component
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->positionComponentId = posCompIndex;
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->size = { 50, 50 };
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->setTexture(textureBot);
		
		//Set his collision component
		factoryFactory->collisionFactory.getComponent(factoryFactory->getEntityCompId(botId, collisionCompId))->positionComponentId = posCompIndex;

		//Create another bot
		botId = factoryFactory->createEntity(std::vector<int>{0, 1, 3}) ;
		posCompIndex = factoryFactory->getEntityCompId(botId, positionCompId);
		factoryFactory->positionFactory.getComponent(posCompIndex)->position = { 800, 600 };
		renderer = drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{ 0, 0, 255, 255 });
		SDL_RenderFillRect(renderer, &rect);
		textureBot = drawer.finishDrawing();
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->positionComponentId = posCompIndex;
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->size = { 50, 50 };
		factoryFactory->rendererFactory.getComponent(factoryFactory->getEntityCompId(botId, rendererCompId))->setTexture(textureBot);
		factoryFactory->collisionFactory.getComponent(factoryFactory->getEntityCompId(botId, collisionCompId))->positionComponentId = posCompIndex;

		//Make the map
		std::array<std::array<int, 25>, 25> map{
			std::array<int, 25>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			std::array<int, 25>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};

		MapRepresentation<25, 25> mapRepresentation{ {0, 0}, map };
		mapRepresentation.transfertToMap(&factoryFactory->map);

	}

	GameCore::GameCore()
	{
		//Initialise the engine
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		factoryFactory = new FactoryFactory;

		camera = new ge::Camera{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		camera->setMinMaxZoom(0.25, 3);

		//Create and add the graphic system to the engine
		std::shared_ptr<GameGraphicSystem> gameGraphic{ new GameGraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		//Add the renderer to the drawer
		ge::Drawer::addRenderer(gameGraphic->getWindowRenderer());
		ge::Engine::getInstance()->addGraphicSystem(gameGraphic);

		//Add the other systems
		movementSystem = std::shared_ptr<MovementSystem>{ new MovementSystem{} };
		ge::Engine::getInstance()->addSystem(movementSystem);
		unsigned int mapRendererId{ factoryFactory->rendererFactory.addComponent(RendererComponent{}) };
		factoryFactory->rendererFactory.getComponent(mapRendererId)->positionComponentId = factoryFactory->positionFactory.addComponent(PositionComponent{});
		std::shared_ptr<MapSystem> mapSystem{ new MapSystem{mapRendererId} };
		ge::Engine::getInstance()->addSystem(mapSystem);
		


		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandZoom{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandResetZoom{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandEntityInfo{}}));
	}

	GameCore::~GameCore() {
		ge::Engine::quit();
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}

	void GameCore::setDestination(unsigned int entityId, ge::Vector2<> destination, bool tileMovement) {
		if (!tileMovement)
			movementSystem->setDestination(factoryFactory->entityFactory.getComponent(entityId)->getComponentId(movementCompId), destination, tileMovement);
		else
			movementSystem->setDestination(factoryFactory->entityFactory.getComponent(entityId)->getComponentId(tileMovementCompId), destination, tileMovement);
	}
}
