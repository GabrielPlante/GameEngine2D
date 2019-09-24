#pragma once
#include "Command.h"
#include "Console.h"
class ToggleConsoleCommand :
	public Command
{
public:
	//Default constructor
	ToggleConsoleCommand()
		:Command("toggleconsole")
	{}

	//Toggle the console
	void execute(const std::vector<float>&) {
		Console::getInstance()->toggle();
	}
};

