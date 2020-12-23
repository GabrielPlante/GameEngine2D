#include "Parameter.h"
#include <iostream>

#include "CommandList.h"

namespace ge {
	Parameter::Parameter(std::string parameterName, float value)
		: value{ value }
	{
		ADD_COMMAND(parameterName, [this](const std::vector<float>& args) {
			if (args.size() == 0)
				std::cout << this->value;
			else if (args.size() == 1)
				this->value = args[0];
			});
	}
}
