#pragma once
#include <SDL.h>
#include <memory>

#include "Publisher.h"

namespace ge {	
	/// <summary>
	/// The EventHandler class need to be derived to have a new event system.
	/// <para>The derived class must override the void update(SDL_Event* event) method that will be called automatically each frame.</para>
	/// <para>The method pollEvent is here to easily poll the event </para>
	/// <para>It is a publisher, so subscriber can subscribe to him to get notified of event</para>
	/// </summary>
	class EventHandler
		: public Publisher
	{
	protected:
		//Poll the next event, return false if there is no more event to pull
		bool pollEvent(SDL_Event* event) { return SDL_PollEvent(event); }
	public:
		//Handle all the event
		virtual void update(SDL_Event* event) = 0;

		//Called when this event handler take the control of the event
		virtual void takeControl() = 0;

		//Called when this event handler lose the control of the event
		virtual void loseControl() = 0;
	};
}
