#include "GameEventHandler.h"
#include "CommandList.h"

#include "ConsoleEventHandler.h"

std::unique_ptr<EventHandler> GameEventHandler::update(SDL_Event* event) {
	while (pollEvent(event)) {
		//If the user want to quit
		if (event->type == SDL_QUIT) {
			CommandList::getInstance()->executeCommand("stop");
		}
		//If the user press a
		else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_a) {
			CommandList::getInstance()->executeCommand("toggleconsole");
			return std::unique_ptr<EventHandler>{new ConsoleEventHandler};
		}
	}

	return nullptr;
}

