#include "GameEventHandler.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Camera.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	void buildTower(int type) {
		ge::Vector2<int> mousPos;
		SDL_GetMouseState(&mousPos.x, &mousPos.y);
		mousPos.x += gv::tileSize / 2;
		mousPos.y += gv::tileSize / 2;
		GameCore::getInstance()->getTowerManager()->buildTower(GameCore::getInstance()->getCamera()->relativeToAbsolute(mousPos.x, mousPos.y), type);
	}

	//Draw a circle : https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
	void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
	{
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
			SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
			SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
			SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}

	ge::Vector2<int> getMousePos() {
		ge::Vector2<int> mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		return mousePos;
	}

	void GameEventHandler::update(SDL_Event* event) {
		while (pollEvent(event)) {
			//If the user want to quit
			if (event->type == SDL_QUIT) {
				ge::CommandList::getInstance()->executeCommand("quit");
			}
			//If a key is pressed
			else if (event->type == SDL_KEYDOWN) {
				//If the key is the a letter on the keyboard
				if (event->key.keysym.sym == SDLK_a) {
					ge::CommandList::getInstance()->executeCommand("openconsole");
				}
				if (event->key.keysym.sym == SDLK_LEFT) {
					cameraMovement.x = -1;
				}
				if (event->key.keysym.sym == SDLK_RIGHT) {
					cameraMovement.x = 1;
				}
				if (event->key.keysym.sym == SDLK_UP) {
					cameraMovement.y = -1;
				}
				if (event->key.keysym.sym == SDLK_DOWN) {
					cameraMovement.y = 1;
				}
			}
			else if (event->type == SDL_KEYUP) {
				if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_RIGHT) {
					cameraMovement.x = 0;
				}
				if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN) {
					cameraMovement.y = 0;
				}
			}
			//If a mouse button is pressed
			else if (event->type == SDL_MOUSEBUTTONDOWN) {
				const ge::Vector2<int> mousePos{ getMousePos() };
				if (event->button.button == SDL_BUTTON_LEFT) {
					if (towerSelected > -1) {
						buildTower(towerSelected);
						towerSelected = -1;
					}
					else {
						for (int i = 0; i != gv::towersValues.size(); i++) {
							if (mousePos.y > 800 - gv::tileSize && mousePos.x < (i + 1) * gv::tileSize) {
								towerSelected = i;
								break;
							}
						}
					}
					if (mousePos.x < 10 * gv::tileSize && mousePos.y < 2 * gv::tileSize && F_FACTORY->gameComponent.startNewWave == interWave) {
						F_FACTORY->gameComponent.startNewWave = goForNextWave;
						F_FACTORY->positionFactory.getComponent(F_FACTORY->uiFactory.getComponent(F_FACTORY->gameComponent.starterUiId)->positionComponentId)
							->setPosition(ge::Vector2<>{0, -gv::tileSize * 2});
					}
				}
				else if (event->button.button == SDL_BUTTON_RIGHT) {
					towerSelected = -1;
				}
			}
			else if (event->type == SDL_MOUSEWHEEL) {
				if (event->wheel.y > 0)
					GameCore::getInstance()->getCamera()->zoom(10/9.0);
				else if (event->wheel.y < 0)
					GameCore::getInstance()->getCamera()->zoom(9/10.0);
			}
		}
		ge::Vector2<> cameraPosition{ GameCore::getInstance()->getCamera()->getRectangle().x, GameCore::getInstance()->getCamera()->getRectangle().y };
		GameCore::getInstance()->getCamera()->setPosition({
			cameraPosition.x + static_cast<long>(cameraMovement.x * ge::Engine::getInstance()->getTimeSinceLastFrame() / gv::speedDividingFactor),
			cameraPosition.y + static_cast<long>(cameraMovement.y * ge::Engine::getInstance()->getTimeSinceLastFrame() / gv::speedDividingFactor) });

		handleTowSelUi();
	}

	void GameEventHandler::handleTowSelUi() {
		//Create the tower ui
		if (towerSelected > -1 && towerSelId == 0) {
			//Draw the texture
			ge::Drawer drawer;
			//Set a lower alpha
			ge::Color uiColor{ gv::towersValues[towerSelected].color };
			uiColor.alpha = 200;
			//Start the rendering proccess
			SDL_Renderer* renderer{ drawer.startDrawing({gv::tileSize, gv::tileSize}, uiColor) };
			ge::Vector2<int> mousPos{ getMousePos() };
			SDL_Rect rect{ ge::Rectangle{0, 0, gv::tileSize, gv::tileSize}.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &rect);
			//Create the position component
			PositionComponent posComp;
			posComp.setPosition(ge::Vector2<double>{ static_cast<double>(mousPos.x), static_cast<double>(mousPos.y) });
			//Create the ui component
			UIComponent uiComp;
			uiComp.positionComponentId = F_FACTORY->positionFactory.addComponent(std::move(posComp));
			uiComp.texture = drawer.finishDrawing(true);
			towerSelId = F_FACTORY->uiFactory.addComponent(std::move(uiComp));

			//Draw the tower range
			renderer = drawer.startDrawing({ gv::towersValues[towerSelected].range * 2, gv::towersValues[towerSelected].range * 2 }, { 255, 255, 255 });
			drawCircle(renderer, gv::towersValues[towerSelected].range, gv::towersValues[towerSelected].range, gv::towersValues[towerSelected].range);

			//Create the components and add them to the factory
			PositionComponent circlePos;
			RendererComponent circleComp;
			circleComp.positionComponentId = F_FACTORY->positionFactory.addComponent(std::move(circlePos));
			circleComp.texture = drawer.finishDrawing(true);
			towerRangeId = F_FACTORY->rendererFactory.addComponent(std::move(circleComp));
		}
		//Delete the tower ui
		else if (towerSelected == -1 && towerSelId != 0) {
			F_FACTORY->positionFactory.deleteComponent(F_FACTORY->uiFactory.getComponent(towerSelId)->positionComponentId);
			F_FACTORY->uiFactory.deleteComponent(towerSelId);
			towerSelId = 0;
			F_FACTORY->positionFactory.deleteComponent(F_FACTORY->rendererFactory.getComponent(towerRangeId)->positionComponentId);
			F_FACTORY->rendererFactory.deleteComponent(towerRangeId);
			towerRangeId = 0;
		}
		//Move the ui
		else if (towerSelId != 0) {
			ge::Vector2<int> mousePos{ getMousePos() };
			F_FACTORY->positionFactory.getComponent(F_FACTORY->uiFactory.getComponent(towerSelId)->positionComponentId)
				->setPosition(ge::Vector2<double>{ static_cast<double>(mousePos.x), static_cast<double>(mousePos.y) });
			ge::Vector2<long> circlePos{ GameCore::getInstance()->getCamera()->relativeToAbsolute(mousePos.x, mousePos.y) };
			circlePos.x += 25 - gv::towersValues[towerSelected].range;
			circlePos.y += 25 - gv::towersValues[towerSelected].range;
			F_FACTORY->positionFactory.getComponent(F_FACTORY->rendererFactory.getComponent(towerRangeId)->positionComponentId)
				->setPosition(ge::Vector2<long>{circlePos.x, circlePos.y});
		}
	}
}
