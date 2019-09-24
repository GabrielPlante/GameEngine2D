#include "Console.h"
#include "CommandList.h"

//Initialize static attribute
Console* Console::instance{ nullptr };

void Console::init(Rectangle coordinate, Color backgroundColor, Color borderColor, int borderSize, int textHeight, int margin)
{
	if (!instance) {
		instance = new Console(coordinate, backgroundColor, borderColor, borderSize, textHeight, margin);
	}
}

void Console::quit() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

Console::Console(Rectangle coordinate, Color backgroundColor, Color borderColor, int borderSize, int textHeight, int margin)
	//The input bar
	:inputBar{ RenderableRectangle{static_cast<int>(coordinate.w - 2 * borderSize - 2 * margin), static_cast<int>(textHeight), backgroundColor},
		Position<>{coordinate.x + borderSize + margin, coordinate.y + coordinate.h - borderSize - textHeight - margin} },
	//The text area
	textArea{ Rectangle{static_cast<long>(coordinate.x + borderSize + margin), static_cast<long>(coordinate.y + borderSize + margin),
	static_cast<long>(coordinate.w - 2 * borderSize - 2 * margin), static_cast<long>(coordinate.h - 2 * textHeight - 2 * borderSize - 3 * margin), }, textHeight },
	coordinate{ coordinate }, backgroundColor{ backgroundColor }, borderColor{ borderColor }, borderSize{ borderSize }, textHeight{ textHeight }, margin{ margin }
{}

void Console::update(SDL_Renderer* renderer) {
	inputBar.update(renderer);
	textArea.update(renderer);
	if (opened) {
		if (needToPressEnter)
			enterText();
	}
}

void Console::render(SDL_Renderer* renderer) const {
	if (opened) {
		//First render the background
		SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(backgroundColor.red), static_cast<Uint8>(backgroundColor.green), static_cast<Uint8>(backgroundColor.blue), static_cast<Uint8>(backgroundColor.alpha));
		SDL_Rect background{ coordinate.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &background);
		//Render the input bar 
		inputBar.render(renderer);
		textArea.render(renderer);
		//Then render the border
		SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(borderColor.red), static_cast<Uint8>(borderColor.green), static_cast<Uint8>(borderColor.blue), static_cast<Uint8>(borderColor.alpha));
		//upper left to upper right
		SDL_Rect topBorder{ Rectangle{ coordinate.x, coordinate.y, coordinate.w, borderSize }.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &topBorder);
		//upper right to bottom right
		SDL_Rect rightBorder{ Rectangle{ coordinate.x + coordinate.w - borderSize, coordinate.y, borderSize, coordinate.h }.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &rightBorder);
		//bottom left to bottom right
		SDL_Rect bottomBorder{ Rectangle{ coordinate.x, coordinate.y + coordinate.h - borderSize, coordinate.w, borderSize }.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &bottomBorder);
		//upper left to bottom left
		SDL_Rect leftBorder{ Rectangle{ coordinate.x, coordinate.y, borderSize, coordinate.h }.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &leftBorder);
		//The bar above the input bar
		SDL_Rect middleBorder{ Rectangle{ coordinate.x, coordinate.y + coordinate.h - borderSize * 2 - textHeight - margin * 2, coordinate.w, borderSize }.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &middleBorder);
	}
}

void Console::enterText() {
	if (inputBar.getInputText().size() > 0 && !inputBar.doesNeedRendering()) {
		textArea.addText(inputBar.clear());
		needToPressEnter = false;
	}
	else if (inputBar.doesNeedRendering())
		needToPressEnter = true;
}

/*void Console::enterCommand(const CommandList& commandList, GameLoop* gameLoop) {
	try {
		TextToCommand textToCommand{ getCommand() };
		commandList.executeCommand(textToCommand.getCommandName(), gameLoop, textToCommand.getArgs());
	}
	catch (CommandError ex) {
		enterText();
		TextArea::addText(ex.what(), Color{ 255, 100, 100 });
		return;
	}
	enterText();
}*/

void Console::toggle() {
	if (!opened) {
		opened = true;
		inputBar.open();
	}
	else {
		opened = false;
		inputBar.close();
	}
}
