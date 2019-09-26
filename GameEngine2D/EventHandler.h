#pragma once
#include <SDL.h>
#include <memory>

namespace ge {
	class EventHandler
	{
	protected:
		//Poll the next event, return false if there is no more event to pull
		bool pollEvent(SDL_Event* event) { return SDL_PollEvent(event); }
	public:
		//Handle all the event
		virtual void update(SDL_Event* event) = 0;
	};
}
