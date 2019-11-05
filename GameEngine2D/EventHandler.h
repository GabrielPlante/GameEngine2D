#pragma once
#include <SDL.h>
#include <memory>

namespace ge {	
	/// <summary>
	/// The EventHandler class need to be derived to have a new event system.
	/// <para> The derived class must override the void update(SDL_Event* event) method that will be called automatically each frame.</para>
	/// <para> The method pollEvent is here to easily poll the event </para>
	/// </summary>
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
