#include "RectangleCreator.h"

#include "Rectangle.h"
#include "Drawer.h"

namespace ge {
	RectangleCreator::RectangleCreator(Vector2<int> size, Color color, bool fill, bool blend) {
		//Initialise the drawer
		Drawer drawer;
		//Start the drawing proccess and get the renderer
		SDL_Renderer* renderer{ drawer.startDrawing(size, color) };
		//Build the rectangle the size wanted
		SDL_Rect rect{ Rectangle{0, 0, size.x, size.y}.toSDL_Rect() };
		//Draw the correct type of rectangle into the renderer
		if (fill)
			SDL_RenderFillRect(renderer, &rect);
		else
			SDL_RenderDrawRect(renderer, &rect);
		//Set the texture to the finished drawing
		texture = drawer.finishDrawing(blend);
	}
}
