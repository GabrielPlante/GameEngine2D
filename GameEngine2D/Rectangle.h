#pragma once
#include <SDL.h>
#include "Position.h"

//A simple rectangle
struct Rectangle {
	//The coordinate of the upper left corner of the rectangle
	long int x;
	long int y;
	//The width and height of the rectangle
	int w;
	int h;

	//Default constructor
	Rectangle() {}

	//Constructor taking an SDL_Rect
	Rectangle(const SDL_Rect& rect)
		:x{ rect.x }, y{ rect.y }, w{ rect.w }, h{ rect.h }
	{
	}

	//Constructor taking a Position, the width and the height
	Rectangle(const Position<>& position, const int w, const int h)
		:x{ position.x }, y{ position.y }, w{ w }, h{ h }
	{
	}

	//Constructor taking coordinate as int, the width and the height
	Rectangle(const long int x, const long int y, const int w, const int h)
		:x{ x }, y{ y }, w{ w }, h{ h }
	{
	}

	//Rectangle to SDL_Rect
	SDL_Rect toSDL_Rect() const {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}

	//Check if two rectangle are overlapping, return true if they are
	bool overlap(const Rectangle& rectangle) const {
		//Check if an rectangle is more left than the other
		if (x > rectangle.x + rectangle.w || rectangle.x > x + w)
			return false;
		//Check if an rectangle is above the other
		if (y > rectangle.y + rectangle.h || rectangle.y > y + h)
			return false;
		return true;
	}
};
