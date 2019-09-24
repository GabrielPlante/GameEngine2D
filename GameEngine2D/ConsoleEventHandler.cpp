#include "ConsoleEventHandler.h"
#include "CommandList.h"

#include "Console.h"

void ConsoleEventHandler::update(SDL_Event* event) {
	while (pollEvent(event)) {
		//If the user want to quit
		if (event->type == SDL_QUIT) {
			CommandList::getInstance()->executeCommand("stop");
		}
		//If the user input text
		else if (event->type == SDL_TEXTINPUT) {
			std::string text;
			text += event->text.text;
			Console::getInstance()->write(text);
		}
	}

}
