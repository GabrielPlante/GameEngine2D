#pragma once
#include <SDL.h>

namespace ge {
	struct Color {
		//The color composant
		Uint8 red{ 0 };
		Uint8 green{ 0 };
		Uint8 blue{ 0 };
		Uint8 alpha{ 0 };

		//Default constructor
		Color() {}

		//Constructor with the color
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
			:red{ r }, green{ g }, blue{ b }, alpha{ a }
		{}

		//Color to SDL_Color
		SDL_Color toSDLColor() const { return SDL_Color{ red, green, blue, alpha }; }
	};
}
