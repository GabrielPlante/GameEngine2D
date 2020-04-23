#pragma once
#include "Command.h"
#include "Engine.h"

namespace ge {
	class CommandTimeScale
		: public Command
	{
	public:
		//Constructor
		CommandTimeScale() : Command{ "time_scale" } {}

		void execute(const std::vector<float>& args) {
			if (args.size() == 1)
				Engine::getInstance()->setTimeScale(static_cast<double>(args[0]));
		}
	};
}
