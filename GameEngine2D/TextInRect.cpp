#include "TextInRect.h"

namespace ge {
	TextInRect::TextInRect(RenderableRectangle graphicRect, const std::string& text, SDL_Renderer* renderer, Vector2<> position, Vector2<> textPosition, const Font& font, Color textColor,
		int borderSize, Color borderColor)
		: RenderableRectangle{ graphicRect }, Text{ text, textPosition, renderer, font, textColor }, position{ position }, borderSize{ borderSize }, borderColor{ borderColor }
	{
	}

	TextInRect::TextInRect(Color backgroundColor, const std::string& text, SDL_Renderer* renderer, Vector2<> position, const Font& font, Color textColor,
		int borderSize, int textMargin, Color borderColor)
		: TextInRect{ RenderableRectangle{static_cast<int>(font.getWidth(text) + 2 * borderSize + 2 * textMargin), static_cast<int>(font.getHeight() * 5 / 6 + 2 * borderSize + 2 * textMargin), backgroundColor },
		text, renderer, position, Vector2<>{position.x + borderSize + textMargin, position.y + borderSize + textMargin}, font, textColor, borderSize, borderColor }
	{}

	void TextInRect::render(SDL_Renderer* renderer, SDL_Rect* srcRect, SDL_Rect* dstRect) const {
		RenderableRectangle::renderWithoutCamera(renderer, position, dstRect);
		Text::render(renderer, srcRect, dstRect);
		//render the border if any
		if (borderSize) {
			//render the border
			SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(borderColor.red), static_cast<Uint8>(borderColor.green), static_cast<Uint8>(borderColor.blue), static_cast<Uint8>(borderColor.alpha));

			//upper left to upper right
			SDL_Rect topBorder{ Rectangle{ position.x, position.y, RenderableRectangle::getW(), borderSize }.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &topBorder);

			//upper right to bottom right
			SDL_Rect rightBorder{ Rectangle{ position.x + RenderableRectangle::getW() - borderSize, position.y, borderSize, RenderableRectangle::getH() }.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &rightBorder);

			//bottom left to bottom right
			SDL_Rect bottomBorder{ Rectangle{ position.x, position.y + RenderableRectangle::getH() - borderSize, RenderableRectangle::getW(), borderSize }.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &bottomBorder);

			//upper left to bottom left
			SDL_Rect leftBorder{ Rectangle{ position.x, position.y, borderSize, RenderableRectangle::getH() }.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &leftBorder);
		}
	}
}
