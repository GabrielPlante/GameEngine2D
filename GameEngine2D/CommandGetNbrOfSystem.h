#pragma once

#include "Command.h"
#include "Engine.h"
#include "Console.h"

namespace ge {
	class CommandGetNbrOfSystem 
		: public Command
	{
	public:
		//Constructor
		CommandGetNbrOfSystem() 
			: Command{ "get_nbr_of_system" }
		{}

		//Print in the console the number of system in the engine
		void execute(const std::vector<float>&) override {
			CONSOLE_LOG(std::to_string(Engine::getInstance()->getSystemSize()));
		}
	};
}
