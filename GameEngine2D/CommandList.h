#pragma once
#include "Command.h"
#include <unordered_set>
#include <memory>


#define EXEC(X) ge::CommandList::getInstance()->executeCommand(X)
#define EXEC_ARGS(X, Y) ge::CommandList::getInstance()->executeCommand(X, Y)

namespace ge {
	class Command;

	struct CommandHash {
		size_t operator()(const std::unique_ptr<Command>& c1) const {
			return std::hash<std::string>{}(c1->getName());
		}
	};
	struct CommandEqual {
		bool operator()(const std::unique_ptr<Command>& c1, const std::unique_ptr<Command>& c2) const {
			return c1->getName() == c2->getName();
		}
	};

	//Singleton, hold all the command
	class CommandList
	{
	private:
		std::unordered_set<std::unique_ptr<Command>, CommandHash, CommandEqual> commandList;

		static CommandList* instance;

		//Default constructor, all the command intern to the engine are put in the list here
		CommandList();

	public:
		//Initialise the class
		static void init();

		//Get the instance of the class, or nullptr if it's not initialized
		static CommandList* getInstance() { return instance; }

		//Destroy this instance of the command list
		static void quit();

		//Add a command to the list
		void addCommand(std::unique_ptr<Command> command) { commandList.insert(std::move(command)); }

		//Try to execute a command. Return true if the command executed properly
		bool executeCommand(const std::string& commandName, const std::vector<float>& args = std::vector<float>{}) const;
	};
}
