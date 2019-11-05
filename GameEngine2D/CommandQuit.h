#pragma once
#include "Command.h"
#include "Engine.h"

namespace ge {
	class CommandQuit :
		public Command
	{
	public:
		//Default constructor
		CommandQuit()
			:Command("quit")
		{}

		//Stop the engine
		void execute(const std::vector<float>&) {
			Engine::getInstance()->stop();
		}
	};
}
