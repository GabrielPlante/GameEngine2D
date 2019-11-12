#include "GameEventHandler.h"

#include "../GameEngine2D/CommandList.h"

namespace ian {

	void GameEventHandler::update(SDL_Event* event) {
		while (pollEvent(event)) {
			//If the user want to quit
			if (event->type == SDL_QUIT) {
				ge::CommandList::getInstance()->executeCommand("quit");
			}
		}
	}
}
