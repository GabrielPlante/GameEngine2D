#pragma once
#include "Command.h"

namespace ge {
	class CommandFps : public Command
	{
	public:
		//Default constructor
		CommandFps() :Command{ "fps" }{}

		void execute(const std::vector<float>& args);

	};
}
