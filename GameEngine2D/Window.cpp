#include "Window.h"
#include <SDL_ttf.h>
#include <stdexcept>

#include "Drawer.h"

namespace ge {
	Window::Window(const int screenWidth, const int screenHeight, const std::string& title)
		:screenWidth{ screenWidth }, screenHeight{ screenHeight }
	{
		//Create window
		gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (!gWindow)
			throw std::runtime_error("SDL_CreateWindow failed");


		//Create renderer
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!gRenderer)
			throw std::runtime_error("SDL_CreateRenderer failed");

		//Everything will be painted black
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

		//Alpha blending https://wiki.libsdl.org/SDL_BlendMode
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

		//Add the renderer to the drawer
		Drawer::addRenderer(gRenderer);
	}

	Window::~Window()
	{
		//Destroy
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gRenderer = nullptr;
		gWindow = nullptr;
	}
}

