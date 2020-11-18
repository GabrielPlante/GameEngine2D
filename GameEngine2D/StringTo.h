#pragma once
#include <string>
#include <stdexcept>

#include <iostream>

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
				std::cout << "String to float error: Arguments must be float" << std::endl;
			}
			catch (const std::out_of_range& ex) {
				std::string string{ ex.what() };
				std::cout << "String to float error: " + string << std::endl;
			}
			return value;
		}

	};
}
