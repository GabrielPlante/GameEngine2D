#include "Engine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>

Engine::SDLInit::SDLInit() {
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL_Init failed");

	//Initialise SDL_ttf
	if (TTF_Init() < 0)
		throw std::runtime_error("TTF_Init failed");
}

Engine::SDLInit::~SDLInit() {
	//Quit SDL_ttf
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}
