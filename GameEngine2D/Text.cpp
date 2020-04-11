#include "Text.h"
#include <iostream>


namespace ge {
	Text::Text(const std::string& text, const Vector2<>& position, SDL_Renderer* renderer, const Font& font, const Color& color)
		:color{ color }
	{
		//To compensate for strange ttf behaviour
		const int positionY = position.y - font.getHeight() / 5;

		//Create the rectangle representing the position of the text
		rect = Rectangle{ position.x, positionY, font.getWidth(text), font.getHeight() };

		//Create the surface
		SDL_Surface* surfaceText{ TTF_RenderText_Solid(font.getFont(), text.c_str(), color.toSDLColor()) };
		if (!surfaceText) {
			std::cout << SDL_GetError() << std::endl;
			throw std::runtime_error("Could not create SDL_Surface !");
		}

		//Transform the surface into a texture
		texture = SDL_CreateTextureFromSurface(renderer, surfaceText);
		if (!texture) {
			std::cout << SDL_GetError() << std::endl;
			throw std::runtime_error("Could not create SDL_Texture !");
		}

		//Release the surface
		SDL_FreeSurface(surfaceText);
	}

	void Text::render(SDL_Renderer* renderer, SDL_Rect* srcRect, SDL_Rect* dstRect) const {
		//Due to strange ttf behaviour
		if (srcRect)
			srcRect->h = srcRect->h * 6 / 5;
		SDL_Rect textRectangle{ rect.toSDL_Rect() };
		SDL_RenderCopy(renderer, texture, srcRect, dstRect ? dstRect : &textRectangle);
	}

	Text::~Text()
	{
		SDL_DestroyTexture(texture);
	}
}
