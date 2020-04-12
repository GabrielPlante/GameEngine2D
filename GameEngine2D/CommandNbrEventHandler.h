#pragma once

#include "Command.h"
#include "Engine.h"
#include "Console.h"

namespace ge {
	class CommandNbrEventHandler 
		: public Command
	{
	public:
		//Constructor
		CommandNbrEventHandler() 
			: Command{ "nbr_of_event_handler" }
		{}

		//Print in the console the number of system in the engine
		void execute(const std::vector<float>&) override {
			CONSOLE_LOG(std::to_string(Engine::getInstance()->getEventHandlerPileSize()));
		}
	};
}
