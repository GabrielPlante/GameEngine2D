#include "GameEventHandler.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {

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
				else if (event->key.keysym.sym == SDLK_LEFT) {
					cameraMovement.x = -1;
				}
				else if (event->key.keysym.sym == SDLK_RIGHT) {
					cameraMovement.x = 1;
				}
				else if (event->key.keysym.sym == SDLK_UP) {
					cameraMovement.y = -1;
				}
				else if (event->key.keysym.sym == SDLK_DOWN) {
					cameraMovement.y = 1;
				}
			}
			else if (event->type == SDL_KEYUP) {
				if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_RIGHT) {
					cameraMovement.x = 0;
				}
				else if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN) {
					cameraMovement.y = 0;
				}
			}
			//If a mouse button is pressed
			/*else if (event->type == SDL_MOUSEBUTTONDOWN) {
				if (event->button.button == SDL_BUTTON_RIGHT) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					ge::Vector2<> mouseCoordinate{ GameCore::getInstance()->getCamera()->relativeToAbsolute(event->button.x, event->button.y) };
					GameCore::getInstance()->setDestination(GameCore::getInstance()->getPlayerId(), mouseCoordinate, true);
				}
			}*/
			else if (event->type == SDL_MOUSEWHEEL) {
				if (event->wheel.y > 0)
					GameCore::getInstance()->getCamera()->zoom(10/9.0);
				else if (event->wheel.y < 0)
					GameCore::getInstance()->getCamera()->zoom(9/10.0);
			}
		}
		ge::Vector2<> cameraPosition{ GameCore::getInstance()->getCamera()->getRectangle().x, GameCore::getInstance()->getCamera()->getRectangle().y };
		GameCore::getInstance()->getCamera()->setPosition({
			cameraPosition.x + static_cast<long>(cameraMovement.x * ge::Engine::getInstance()->getTimeSinceLastFrame() / speedDividingFactor),
			cameraPosition.y + static_cast<long>(cameraMovement.y * ge::Engine::getInstance()->getTimeSinceLastFrame() / speedDividingFactor) });
	}
}
