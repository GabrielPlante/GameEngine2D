#include "CommandList.h"

#include "BaseCommand.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	CommandList* CommandList::instance{ nullptr };

	void CommandList::init() {
		if (!instance) {
			instance = new CommandList{};
		}
	}

	void CommandList::quit() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}

	CommandList::CommandList()
	{
		addCommand("nbr_of_system", CommandNbrOfSystem);
		addCommand("time_scale", CommandTimeScale);
		addCommand("quit", CommandQuit);
		addCommand("fps", CommandFps);
	}

	bool CommandList::executeCommand(const std::string& commandName, const std::vector<float>& args) const {
		if (commandList.find(commandName) != commandList.end()) {
			commandList.find(commandName)->second(args);
			return true;
		}
#ifdef DEBUG_GE
		std::cout << "Command " << commandName << " not found" << std::endl;
#endif // DEBUG_GE

		return false;
	}
}