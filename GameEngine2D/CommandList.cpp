#include "CommandList.h"
#include "Command.h"

#include "StopCommand.h"

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
	commandList.insert(std::move(std::unique_ptr<Command>{new StopCommand{}}));
}

bool CommandList::executeCommand(const std::string& commandName, const std::vector<float>& args) const {
	std::unique_ptr<Command> command{ new Command{commandName} };
	auto search = commandList.find(command);
	if (search == commandList.end())
		return false;
	(**search).execute(args);
	return true;
}