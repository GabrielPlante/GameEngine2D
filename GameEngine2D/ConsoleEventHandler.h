#pragma once
#include "EventHandler.h"

namespace ge {
	class ConsoleEventHandler :
		public EventHandler
	{
	public:
		//Update the console
		std::unique_ptr<EventHandler> update(SDL_Event* event) override;
	};

}
