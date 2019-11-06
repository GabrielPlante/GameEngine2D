#pragma once
#include <SDL.h>
#include <memory>
#include <vector>

#include "System.h"

#include "EventHandler.h"


namespace ge {
	/// <summary>
	/// The event system class is where every event (given by an SDL_Event) are handled
	/// </summary>
	class EventSystem :
		public System
	{
	private:
		//The pile used to determine wich event handler is used (the top one is used)
		std::vector<std::unique_ptr<EventHandler>> eventHandlerPile;

		SDL_Event event{ 0 };

	public:
		//Default constructor
		EventSystem() {}

		//What will update all component under this system control
		void update();

		//Push an event handler that will be used from now on
		void pushEventHandler(std::unique_ptr<EventHandler> eventHandler);

		//Pop the top event, the next one will be used from now on
		void popEventHandler();

		//As a subscriber, the system need to be able to handle message, however this system will not use it
		void handleMessage(std::shared_ptr<Message> message) override {}
	};

}
