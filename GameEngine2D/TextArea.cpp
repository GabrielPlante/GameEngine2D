#include "TextArea.h"

TextArea::TextArea(const Rectangle& position, int textHeight, const std::string& fontFileName)
	:position{ position }, font{ textHeight, fontFileName }
{
}

void TextArea::render(SDL_Renderer* renderer) {
	addPendingText(renderer);
	for (int i = static_cast<int>(textList.size()) - 1; i >= 0; i--) {
		Rectangle textPosition{ position.x, position.y + position.h - font.getHeight() * (static_cast<long>(textList.size()) - i), textList[i]->getRect().w, textList[i]->getRect().h };
		if (textPosition.y < position.y)
			break;
		SDL_Rect textPositionSDL{ textPosition.toSDL_Rect() };
		textList[i]->render(renderer, nullptr, &textPositionSDL);
	}
}

void TextArea::addPendingText(SDL_Renderer* renderer) {
	while (!textToRender.empty()) {
		addText(std::unique_ptr<Text>{new Text{ textToRender.front(), Position<>{0, 0}, renderer, font, textColor.front() }});
		textToRender.pop();
		textColor.pop();
	}
}
