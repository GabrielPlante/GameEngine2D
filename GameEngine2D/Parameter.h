#pragma once
#include <string>


namespace ge {
	// A parameter is a simple value but with command tied to it that allow to know and change it's value from anywhere via the command system
	struct Parameter
	{
	public:
		//The actual value
		float value;

		//Constructor, the paramater name is the name of the command tied to the parameter
		Parameter(std::string parameterName, float value = 0);

		//Implicit conversion to float
		operator float() const { return value; }
	};
}

