#pragma once
#include "StringSplit.h"
#include "StringTo.h"

struct TextToCommand {
private:
	std::string commandName;
	std::vector<float> args;
public:
	//Constructor, also proccess a string to convert it in a command
	TextToCommand(const std::string& string) {
		if (string != "") {
			std::vector<std::string> splited = StringSplit::split(string, ' ');
			commandName = splited[0];
			for (int i = 1; i != splited.size(); i++)
				args.push_back(StringTo::toFloat(splited[i]));
		}
		else
			commandName = "";
	}

	//Get the string representing the command name
	const std::string& getCommandName() const { return commandName; }
	
	//Get the arguments of the command
	const std::vector<float>& getArgs() const { return args; }
};
