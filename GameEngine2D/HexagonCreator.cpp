#include "HexagonCreator.h"
#include <math.h>

#include "RectangleCreator.h"
#include "Drawer.h"

namespace ge {
	HexagonCreator::HexagonCreator(int size, Color color, bool blend) {
		TextureWrapper square{ RectangleCreator{{size, size}, color, blend}.getTexture() };

		Drawer drawer;
		int width{ static_cast<int>(ceil(sqrt(3.0) * size)) };
		SDL_Renderer* renderer{ drawer.startDrawing({width, 2 * size}, color) };
		//Creating the rect for the position
		SDL_Rect rect{ square.getTextureRect() };
		rect.y = size / 2;

		//Left part
		//Render the left square
		SDL_RenderCopy(renderer, square.get(), NULL, &rect);
		//Render the top left square
		SDL_Point rotationPoint{ ge::Vector2<int>{0, 0}.toSDL_Point() };
		SDL_RenderCopyEx(renderer, square.get(), NULL, &rect, 330, &rotationPoint, SDL_FLIP_HORIZONTAL);
		//Render the bottom left square
		if (size % 2 == 1)
			rect.x--;
		rotationPoint.y = size;
		SDL_RenderCopyEx(renderer, square.get(), NULL, &rect, 30, &rotationPoint, SDL_FLIP_HORIZONTAL);

		//Right part
		rect.x = width / 2;
		if (size % 2 == 1)
			rect.x++;
		//Render the right square
		SDL_RenderCopy(renderer, square.get(), NULL, &rect);
		//Render the bottom right square
		rect.y = size;
		SDL_RenderCopyEx(renderer, square.get(), NULL, &rect, 330, &rotationPoint, SDL_FLIP_HORIZONTAL);
		//Render the top righ square
		rect.y = 0;
		rotationPoint.y = 0;
		rotationPoint.x = 0;
		SDL_RenderCopyEx(renderer, square.get(), NULL, &rect, 30, &rotationPoint, SDL_FLIP_HORIZONTAL);

		texture = drawer.finishDrawing(blend);
	}
}
