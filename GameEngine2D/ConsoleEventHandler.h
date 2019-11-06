#pragma once
#include "EventHandler.h"

#include "Console.h"

namespace ge {
	class ConsoleEventHandler :
		public EventHandler
	{
	public:
		//Update the console
		void update(SDL_Event* event) override;

		//When this take the event control
		void takeControl() override { Console::getInstance()->open(); }

		//When this lose the event control
		void loseControl() override { Console::getInstance()->close(); }
	};

}
