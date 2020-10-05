#include "CircleCreator.h"

#include "Drawer.h"

namespace ge {
	//Adapted from
	//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
	CircleCreator::CircleCreator(int32_t radius, Color color, bool disk, bool blend) {
		Drawer drawer;

		const int32_t diameter = (radius * 2);
		SDL_Renderer* renderer{ drawer.startDrawing({ diameter, diameter }, color) };

		int32_t centreX{ radius };
		int32_t centreY{ radius };

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			if (disk) {
				//  Each of the following renders an octant of the circle
				SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX - x, centreY - y);
				SDL_RenderDrawLine(renderer, centreX + x, centreY + y, centreX - x, centreY + y);
				SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX - y, centreY - x);
				SDL_RenderDrawLine(renderer, centreX + y, centreY + x, centreX - y, centreY + x);
			}
			else {
				//  Each of the following renders an octant of the circle
				SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
				SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
				SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
				SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
				SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
				SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
				SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
				SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
			}

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}

		texture = drawer.finishDrawing(blend);
	}
}
