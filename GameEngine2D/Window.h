#pragma once
#include <SDL.h>

class Window
{
private:
	SDL_Window* gWindow{ nullptr };
	SDL_Renderer* gRenderer{ nullptr };

	const int screenWidth;
	const int screenHeight;
public:
	//Constructor
	Window(const int screenWith, const int screenHeight);

	//Clear the window (call before drawing anything)
	void clear() {
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
	}

	//Render the window (call after drawing everything)
	void update() { SDL_RenderPresent(gRenderer); }

	//Get the renderer, required to draw anything
	SDL_Renderer* getRenderer() { return gRenderer; }

	//Destructor
	~Window();
};
