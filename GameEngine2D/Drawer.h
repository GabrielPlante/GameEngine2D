#pragma once
#include <SDL.h>

#include "TextureWrapper.h"
#include "Vector2.h"
#include "Color.h"

namespace ge {
	
	///The drawer class is used to create a texture
	class Drawer {
	private:
		//The global renderer
		static SDL_Renderer* renderer;

		SDL_Texture* texture{ nullptr };
	public:
		//Add the renderer to the drawer. Needed to make the class work
		static void addRenderer(SDL_Renderer* newRenderer);

		//Start the drawing on the given renderer
		SDL_Renderer* startDrawing(Vector2<int> size, Color color, Uint32 format = SDL_PIXELFORMAT_RGBA8888);

		//Finish the drawing process and get the texture that represent the drawing
		TextureWrapper finishDrawing(bool blend = false);
	};
}
