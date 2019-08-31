#pragma once
#include <vector>

/*
 * The command class is used to represent every input the user could have on the game
*/
class Command
{
public:
	//Execute the command
	virtual void execute(std::vector<float> args) = 0;
};

