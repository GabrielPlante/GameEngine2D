#include "CommandList.h"
#include "Command.h"
#include "CommandError.h"

#include "Console.h"

#include "CommandQuit.h"
#include "CommandFps.h"

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
		commandList.insert(std::move(std::unique_ptr<Command>{new CommandQuit{}}));
		commandList.insert(std::move(std::unique_ptr<Command>{new CommandFps{}}));

		CONSOLE_LOG("Command list successfully initialised");
	}

	bool CommandList::executeCommand(const std::string& commandName, const std::vector<float>& args) const {
		std::unique_ptr<Command> command{ new Command{commandName} };
		auto search = commandList.find(command);
		if (search == commandList.end()) {
			CONSOLE_LOG_ERROR("Command \"" + commandName + "\" not found");
			return false;
		}
		(**search).execute(args);
		return true;
	}
}