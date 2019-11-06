#include "ConsoleEventHandler.h"
#include "CommandList.h"

#include "Console.h"

namespace ge {
	void ConsoleEventHandler::update(SDL_Event* event) {
		while (pollEvent(event)) {
			//If the user want to quit
			if (event->type == SDL_QUIT) {
				CommandList::getInstance()->executeCommand("quit");
			}
			//If the user want to quit the console
			else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) {
				CommandList::getInstance()->executeCommand("quitconsole");
			}
			//Return is pressed, enter the command typed
			else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN) {
				Console::getInstance()->pushCommand();
			}
			//if the user want to delete the last character
			else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE) {
				Console::getInstance()->popText();
			}
			//If the user input text
			else if (event->type == SDL_TEXTINPUT) {
				std::string text;
				text += event->text.text;
				Console::getInstance()->write(text);
			}
			//Scrolling
			else if (event->type == SDL_MOUSEWHEEL) {
				Console::getInstance()->verticalScroll(event->wheel.y);
			}
		}
	}
}
