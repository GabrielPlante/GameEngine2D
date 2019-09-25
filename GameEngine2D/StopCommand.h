#pragma once
#include "Command.h"
#include "Engine.h"

namespace ge {
	class StopCommand :
		public Command
	{
	public:
		//Default constructor
		StopCommand()
			:Command("stop")
		{}

		//Stop the engine
		void execute(const std::vector<float>&) {
			Engine::getInstance()->stop();
		}
	};
}
