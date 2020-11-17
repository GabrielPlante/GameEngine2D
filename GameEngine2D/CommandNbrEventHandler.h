#pragma once

#include "Command.h"
#include "Engine.h"

#include <iostream>

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
			std::cout << (std::to_string(Engine::getInstance()->getEventHandlerPileSize())) << std::endl;
		}
	};
}
