#pragma once
#include <unordered_map>
#include <functional>

#define EXEC(NAME) ge::CommandList::getInstance()->executeCommand(NAME)
#define EXEC_ARGS(NAME, ARGS) ge::CommandList::getInstance()->executeCommand(NAME, ARGS)

#define ADD_COMMAND(NAME, FUNCTION) ge::CommandList::getInstance()->addCommand(NAME, FUNCTION)

namespace ge {
	//Singleton, hold all the command
	class CommandList
	{
	private:
		std::unordered_map<std::string, std::function<void(const std::vector<float>&)>> commandList;

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

		//Add a command to the list, return true if the command is successfully inserted
		bool addCommand(const std::string& commandName, std::function<void(const std::vector<float>&)> function) { return commandList.insert(std::make_pair(commandName, function)).second; }

		//Try to execute a command. Return true if the command is executed properly
		bool executeCommand(const std::string& commandName, const std::vector<float>& args = std::vector<float>{}) const;

		//Remove a command from the list
		void removeCommand(const std::string& commandName) { commandList.erase(commandName); }
	};
}
