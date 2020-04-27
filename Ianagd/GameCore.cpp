#include "GameCore.h"
#include <SDL.h>

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/TextInRect.h"
#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Camera.h"
#include "../GameEngine2D/Drawer.h"

#include "MapRepresentation.h"
#include "FactoryFactory.h"
#include "GameValues.h"

//The systems
#include "EnemyManagerSystem.h"
#include "DamageDealerSystem.h"
#include "ShotRendererSystem.h"
#include "GameGraphicSystem.h"
#include "MovementSystem.h"
#include "GameSystem.h"
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

		//Create all the other systems
		std::shared_ptr<MovementSystem> movementSystem{ new MovementSystem{} };
		unsigned int mapRendererId{ factoryFactory->rendererFactory.addComponent(RendererComponent{}) };
		std::shared_ptr<MapSystem> mapSystem{ new MapSystem{mapRendererId} };
		std::shared_ptr<ShotRendererSystem> shotRendererSystem{ new ShotRendererSystem{} };
		std::shared_ptr<GameSystem> gameSystem{ new GameSystem{} };
		std::shared_ptr<DamageDealerSystem> damageDealerSystem{ new DamageDealerSystem{} };
		std::shared_ptr<EnemyManagerSystem> enemyManagerSystem{ new EnemyManagerSystem{{0, 2}, {22, 24} } };

		//Add them to the engine
		ge::Engine::getInstance()->addSystem(enemyManagerSystem);
		ge::Engine::getInstance()->addSystem(damageDealerSystem);
		ge::Engine::getInstance()->addSystem(shotRendererSystem);
		ge::Engine::getInstance()->addSystem(movementSystem);
		ge::Engine::getInstance()->addSystem(gameSystem);
		ge::Engine::getInstance()->addSystem(mapSystem);

		factoryFactory->rendererFactory.getComponent(mapRendererId)->positionComponentId = factoryFactory->positionFactory.addComponent(PositionComponent{});
		
		//Add the command to the command list
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandZoom{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandResetZoom{}}));
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandEntityInfo{}}));

		CONSOLE_LOG("GameCore successfully initialised")
		CONSOLE_LOG("You can use the command quitconsole or the escape button to leave the console")

		ge::CommandList::getInstance()->executeCommand("quitconsole");
	}

	void GameCore::setupGame() {
		//Make the map
		std::array<std::array<int, 25>, 25> map{
			std::array<int, 25>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
			std::array<int, 25>{1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0},
			std::array<int, 25>{0, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0},
			std::array<int, 25>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
		};

		MapRepresentation<25, 25> mapRepresentation{ {0, 0}, map };
		mapRepresentation.transfertToMap(&factoryFactory->map);

		//Workaround for a bug with UI rendering
		ge::Engine::getInstance()->update();

		//Create the texture for the wrapper
		/*ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({gv::tileSize, gv::tileSize}, {0, 0, 255}) };
		SDL_Rect rect{ ge::Rectangle{0, 0, gv::tileSize, gv::tileSize}.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &rect);
		ge::TextureWrapper texture{ drawer.finishDrawing() };

		//Create the tower
		unsigned int towerId{ factoryFactory->createEntity({positionCompId, rendererCompId, damageDealerCompId}) };
		factoryFactory->entityFactory.getComponent(towerId)
			//->managePosition({ factoryFactory->map.relativeToAbsolute({5, 3}) })
			->managePosition({ factoryFactory->map.relativeToAbsolute({9, 13}) })
			->manageRenderer(texture)
			->manageDamageDealer(25, 300, 1000);*/

		//Create a text
		ge::Drawer drawer;
		ge::Rectangle textRect{ SCREEN_WIDTH / 2 - 100, 0, 200, 50 };
		SDL_Renderer* renderer{ drawer.startDrawing({ textRect.w, textRect.h }, { 100, 100, 100, 150 }) };
		ge::TextInRect text{ { 0, 0, 0, 0 }, "Gold:", renderer, { 0, 0 }, ge::Font{ textRect.h }, { 100, 100, 255 } };
		text.render(renderer);

		UIComponent textComponent;
		textComponent.texture = drawer.finishDrawing(true);
		PositionComponent textPos;
		textPos.setPosition(ge::Vector2<>{ textRect.x, textRect.y });
		textComponent.positionComponentId = factoryFactory->positionFactory.addComponent(std::move(textPos));
		factoryFactory->uiFactory.addComponent(std::move(textComponent));

		//Update game values
		factoryFactory->gameComponent.playerGold = gv::startingGold;

		//Create tower button
		for (int i = 0; i != gv::towersValues.size(); i++) {
			renderer = drawer.startDrawing({ gv::tileSize, gv::tileSize }, gv::towersValues[i].color);
			SDL_Rect towerRect{ ge::Rectangle{0, 0, gv::tileSize, gv::tileSize}.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &towerRect);
			//Set the position to the bottom screen
			PositionComponent posTower;
			posTower.setPosition(ge::Vector2<>{i* gv::tileSize, SCREEN_HEIGHT - gv::tileSize});
			UIComponent towerComp;
			towerComp.positionComponentId = factoryFactory->positionFactory.addComponent(std::move(posTower));
			towerComp.texture = drawer.finishDrawing();
			factoryFactory->uiFactory.addComponent(std::move(towerComp));
		}

		//Create the starting button
		ge::Rectangle startRect{ 0, 0, 10 * gv::tileSize, 2 * gv::tileSize };
		renderer = drawer.startDrawing({ startRect.w, startRect.h }, { 100, 100, 100, 100 });
		ge::TextInRect textStart{ { 100, 100, 100, 100 }, "Start wave", renderer, { 0, 0 }, ge::Font{ startRect.h }, { 100, 100, 255 } };
		textStart.render(renderer);
		PositionComponent startPosComp;
		startPosComp.setPosition(ge::Vector2<long>{startRect.x, startRect.y});
		UIComponent startComponent;
		startComponent.positionComponentId = factoryFactory->positionFactory.addComponent(std::move(startPosComp));
		startComponent.texture = drawer.finishDrawing(true);
		factoryFactory->gameComponent.starterUiId = factoryFactory->uiFactory.addComponent(std::move(startComponent));
	}

	void GameCore::endGame() {
		//Create a text
		ge::Drawer drawer;
		ge::Rectangle textRect{ SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50, 400, 100 };
		SDL_Renderer* renderer{ drawer.startDrawing({ textRect.w, textRect.h }, { 0, 0, 0, 0 }) };
		std::string endText;
		if (factoryFactory->gameComponent.startNewWave == 2)
			endText = "You lost !";
		else
			endText = "You win !";
		ge::TextInRect text{ { 0, 0, 0, 0 }, endText, renderer, { 0, 0 }, ge::Font{ textRect.h }, { 255, 50, 50 } };
		text.render(renderer);

		UIComponent textComponent;
		textComponent.texture = drawer.finishDrawing(true);
		PositionComponent textPos;
		textPos.setPosition(ge::Vector2<>{ textRect.x, textRect.y });
		textComponent.positionComponentId = factoryFactory->positionFactory.addComponent(std::move(textPos));
		factoryFactory->uiFactory.addComponent(std::move(textComponent));
	}

	GameCore::~GameCore() {
		ge::Engine::quit();
	}

	void GameCore::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
