#pragma once
#include <SDL.h>
struct Color {
	//The color composant
	int red{ 0 };
	int green{ 0 };
	int blue{ 0 };
	int alpha{ 0 };

	//Default constructor
	Color() {}

	//Constructor with the color
	Color(int r, int g, int b, int a = 255)
		:red{ r }, green{ g }, blue{ b }, alpha{ a }
	{}

	//Color to SDL_Color
	SDL_Color toSDLColor() const { return SDL_Color{ static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue), static_cast<Uint8>(alpha) }; }
};
