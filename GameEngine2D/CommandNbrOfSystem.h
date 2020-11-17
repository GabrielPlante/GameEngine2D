#pragma once

#include "Command.h"
#include "Engine.h"

#include <iostream>

namespace ge {
	class CommandNbrOfSystem 
		: public Command
	{
	public:
		//Constructor
		CommandNbrOfSystem() 
			: Command{ "nbr_of_system" }
		{}

		//Print in the console the number of system in the engine
		void execute(const std::vector<float>&) override {
			std::cout << (std::to_string(Engine::getInstance()->getSystemSize())) << std::endl;
		}
	};
}
