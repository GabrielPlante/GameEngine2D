#pragma once
#include "Command.h"
#include "Engine.h"
class StopCommand:
	public Command
{
public:
	//Stop the engine
	void execute(std::vector<float> args) {
		Engine::getInstance()->stop();
	}
};
