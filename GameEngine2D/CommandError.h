#pragma once
#include <stdexcept>
#include <string>
namespace ge {
	class CommandError
		:public std::runtime_error
	{
	public:
		CommandError(const std::string& error) : std::runtime_error{ error }{}
	private:
		std::string message;
	};
}
