#include "Window.h"
#include <SDL_ttf.h>



Window::Window(const int screenWith, const int screenHeight)
	:screenWidth{ screenWidth }, screenHeight{ screenHeight }
{
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL_Init failed");

	//Create window
	gWindow = SDL_CreateWindow("Ianagd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWith, screenHeight, SDL_WINDOW_SHOWN);
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

	//Temporary solution : initialise ttf in the window
	if (TTF_Init() < 0)
		throw std::runtime_error("TTF_Init failed");
}

Window::~Window()
{
	TTF_Quit();
	//Destroy
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}
