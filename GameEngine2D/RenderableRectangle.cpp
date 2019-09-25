#include "RenderableRectangle.h"
#include "Rectangle.h"

namespace ge {
	RenderableRectangle::RenderableRectangle(int w, int h, Color color)
		:Renderable(), w{ w }, h{ h }, color{ color }
	{
	}

	void RenderableRectangle::render(SDL_Renderer* renderer, const Camera& camera, const Position<>& position) const {
		if (camera.isInCamera(Rectangle{ position, w, h })) {
			//Set the color to be rendered the color of the rectangle
			SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(color.red), static_cast<Uint8>(color.green), static_cast<Uint8>(color.blue), static_cast<Uint8>(color.alpha));
			//Converting the coordinate to relative position
			Position<> relativePosition{ camera.absoluteToRelative(position.x, position.y) };

			SDL_Rect rect{ Rectangle{relativePosition.x, relativePosition.y, w, h}.toSDL_Rect() };
			//Render the rectangle
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	void RenderableRectangle::renderWithoutCamera(SDL_Renderer* renderer, const Position<>& position, SDL_Rect* dstRect) const {
		//Set the color to be rendered the color of the rectangle
		SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(color.red), static_cast<Uint8>(color.green), static_cast<Uint8>(color.blue), static_cast<Uint8>(color.alpha));

		SDL_Rect rect{ Rectangle{position.x, position.y, dstRect ? dstRect->w : w, dstRect ? dstRect->h : h}.toSDL_Rect() };
		//Render the rectangle
		SDL_RenderFillRect(renderer, &rect);
	}
}
