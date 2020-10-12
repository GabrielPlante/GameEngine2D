#include "GameEventHandler.h"

#include "../GameEngine2D/CommandList.h"

namespace ian {
	void GameEventHandler::update(SDL_Event* event) {
		while (pollEvent(event)) {
			//If the user want to quit
			if (event->type == SDL_QUIT) {
				EXEC("quit");
			}
			//If a key is pressed
			else if (event->type == SDL_KEYDOWN) {
				//If the key is the a letter on the keyboard
				if (event->key.keysym.sym == SDLK_a) {
					//ge::CommandList::getInstance()->executeCommand("openconsole");
					EXEC("openconsole");
				}
			}
		}
	}
}
