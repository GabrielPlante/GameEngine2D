#pragma once
#include "System.h"
#include <SDL.h>
class EventSystem :
	public System
{
private:
	SDL_Event event{ 0 };

	//Poll the next event, return false if there is no more event to pull
	bool pollEvent() { return SDL_PollEvent(&event); }
public:
	//Default constructor
	EventSystem() {}

	//What will update all component under this system control
	void update() override;
};

