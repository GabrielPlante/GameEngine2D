#include "GameEventHandler.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"
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
			}
			//If a mouse button is pressed
			else if (event->type == SDL_MOUSEBUTTONDOWN) {
				if (event->button.button == SDL_BUTTON_RIGHT) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					ge::Vector2<> mouseCoordinate{ GameCore::getInstance()->getCamera()->relativeToAbsolute(event->button.x, event->button.y) };
					GameCore::getInstance()->setDestination(GameCore::getInstance()->getPlayerId(), mouseCoordinate, true);
					/*std::cout << "Before the map : " << mouseCoordinate.x << " ; " << mouseCoordinate.y << std::endl;
					ge::Vector2<int> mapCo{ F_FACTORY->map.absoluteToRelative(mouseCoordinate) };
					std::cout << "In the map : " << mapCo.x << " ; " << mapCo.y << std::endl;
					ge::Vector2<> afterCo{ F_FACTORY->map.relativeToAbsolute(mapCo) };
					std::cout << "After the map : " << afterCo.x << " ; " << afterCo.y << std::endl;
					std::cout << "----------------------------" << std::endl;*/
				}
			}
			else if (event->type == SDL_MOUSEWHEEL) {
				if (event->wheel.y > 0)
					GameCore::getInstance()->getCamera()->zoom(10/9.0);
				else if (event->wheel.y < 0)
					GameCore::getInstance()->getCamera()->zoom(9/10.0);
			}
		}
	}
}
