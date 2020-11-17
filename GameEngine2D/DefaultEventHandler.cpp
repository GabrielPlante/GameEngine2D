#include "DefaultEventHandler.h"

#include "CommandList.h"

namespace ge {
	void DefaultEventHandler::update(SDL_Event* event)
	{
		while (pollEvent(event)) {
			//If the user want to quit
			if (event->type == SDL_QUIT) {
				EXEC("quit");
			}
			//If a mouse button is pressed
			/*else if (event->type == SDL_MOUSEBUTTONDOWN) {
			}*/
		}
	}
}
