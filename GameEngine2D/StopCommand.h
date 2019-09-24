#pragma once
#include "Command.h"
#include "Engine.h"
class StopCommand:
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
