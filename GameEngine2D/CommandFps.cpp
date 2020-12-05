#include "CommandFps.h"

#include "Engine.h"

#include <iostream>

constexpr int FPS_MIN{ 5 };

namespace ge {
	void CommandFps::execute(const std::vector<float>& args) {
		if (args.empty()) {
			std::cout << ("FPS " + std::to_string(1 / (static_cast<double>(ENGINE->timeBetweenFrame) / 1000.0))) << std::endl;
		}
		else {
			if (args[0] > FPS_MIN)
				ENGINE->timeBetweenFrame = static_cast<uint32_t>(1000/args[0]);
		}
	}
}