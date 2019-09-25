#pragma once
#include <string>
#include <stdexcept>
#include "Console.h"

namespace ge {
	//To convert a string to another type
	struct StringTo
	{
		//Convert a string to a float
		static float toFloat(const std::string& arg) {
			float value{ 0 };
			try {
				value = std::stof(arg);
			}
			catch (const std::invalid_argument&) {
				CONSOLE_LOG_ERROR("String to float error: Arguments must be float");
			}
			catch (const std::out_of_range& ex) {
				std::string string{ ex.what() };
				CONSOLE_LOG_ERROR("String to float error: " + string);
			}
			return value;
		}

	};
}
