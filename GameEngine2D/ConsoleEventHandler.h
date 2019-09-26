#pragma once
#include "EventHandler.h"

namespace ge {
	class ConsoleEventHandler :
		public EventHandler
	{
	public:
		//Update the console
		void update(SDL_Event* event) override;
	};

}
