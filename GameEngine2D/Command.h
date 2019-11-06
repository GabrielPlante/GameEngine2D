#pragma once
#include <vector>
#include <string>

namespace ge {
	/* The command class is used to represent every input the user could have on the game
	*/
	class Command
	{
	private:
		std::string name;
	public:

		//Constructor
		Command(std::string name)
			:name{ std::move(name) }
		{}

		//Execute the command
		virtual void execute(const std::vector<float>&) {}

		//Return the name of the command
		const std::string& getName() const { return name; }

		//Operator < with another command or another string
		bool operator<(const Command& other) const { return name < other.getName(); }
		bool operator<(const std::string& other) const { return name < other; }
	};

}
