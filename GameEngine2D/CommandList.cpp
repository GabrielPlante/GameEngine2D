#include "CommandList.h"
#include "Command.h"

#include "StopCommand.h"

bool CommandList::isInitialized{ false };
CommandList* CommandList::instance{ nullptr };

void CommandList::init() {
	if (!isInitialized) {
		instance = new CommandList{};
		isInitialized = true;
	}
}

void CommandList::quit() {
	if (isInitialized) {
		delete instance;
		isInitialized = false;
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