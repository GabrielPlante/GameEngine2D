#include "TextArea.h"


TextArea::TextArea(const Rectangle& position, int textHeight, const std::string& fontFileName, const int scrollMultiplier)
	:position{ position }, font{ textHeight, fontFileName }, camera{ position }, scrollMultiplier{ scrollMultiplier }
{
}

void TextArea::update(SDL_Renderer* renderer) {
	addPendingText(renderer);
}

void TextArea::render(SDL_Renderer* renderer) const {
	for (int i = static_cast<int>(textList.size()) - 1; i >= 0; i--) {
		Rectangle textPosition{ position.x, position.y + position.h - font.getHeight() * (static_cast<long>(textList.size()) - i), std::min(textList[i]->getRect().w, position.w), textList[i]->getRect().h };
		//If the text is above the top, no more text will be rendered
		if (textPosition.y < camera.getRectangle().y)
			break;
		if (!camera.isInCamera(textPosition))
			continue;
		textPosition = Rectangle{ camera.absoluteToRelative(textPosition.x + position.x, textPosition.y + position.y), textPosition.w, textPosition.h };
		SDL_Rect textPositionSDL{ textPosition.toSDL_Rect() };
		SDL_Rect textSourceSDL{ Rectangle {0, 0, std::min(textPosition.w, position.w), textPosition.h}.toSDL_Rect() };
		textList[i]->render(renderer, &textSourceSDL, &textPositionSDL);
	}
}

void TextArea::addPendingText(SDL_Renderer* renderer) {
	while (!textToRender.empty()) {
		addText(std::unique_ptr<Text>{new Text{ textToRender.front(), Position<>{0, 0}, renderer, font, textColor.front() }});
		textToRender.pop();
		textColor.pop();
		//Set the camera position to the newly added text
		camera.setPosition(Position<>{position.x, position.y});
	}
}

void TextArea::verticalScroll(int amount) {
	camera.move(0, - amount * scrollMultiplier);
	//Prevent the camera from going to much up
	if (camera.getRectangle().y < position.y - static_cast<int>(textList.size() * font.getHeight()) + position.h) {
		camera.setPosition(Position<>{camera.getRectangle().x, position.y - static_cast<int>(textList.size() * font.getHeight()) + position.h});
	}
	//Prevent the camera from going to much down
	if (camera.getRectangle().y > position.y)
		camera.setPosition(Position<>{camera.getRectangle().x, position.y});
}
