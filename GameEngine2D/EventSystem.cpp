#include "EventSystem.h"
#include "CommandList.h"

#include "Console.h"

void EventSystem::update() {
	while (pollEvent()) {
		if (event.type == SDL_QUIT) {
			CommandList::getInstance()->executeCommand("stop");
		}

		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) {
			CommandList::getInstance()->executeCommand("toggleconsole");
		}
		else if (event.type == SDL_TEXTINPUT && Console::getInstance()->isOpened()) {
			std::string text;
			text += event.text.text;
			Console::getInstance()->write(text);
		}
	}
}
