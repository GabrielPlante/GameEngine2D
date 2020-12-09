#include "BaseCommand.h"
#include <string>

#include "Engine.h"

#include <iostream>

constexpr int FPS_MIN{ 5 };

namespace ge {
	void CommandFps(const std::vector<float>& args) {
		if (args.empty()) {
			std::cout << ("FPS " + std::to_string(1 / (static_cast<double>(ENGINE->timeBetweenFrame) / 1000.0))) << std::endl;
		}
		else {
			if (args[0] > FPS_MIN)
				ENGINE->timeBetweenFrame = static_cast<uint32_t>(1000 / args[0]);
		}
	}

	void CommandQuit(const std::vector<float>&)
	{
		Engine::getInstance()->stop();
	}

	void CommandTimeScale(const std::vector<float>& args)
	{
		if (args.size() == 1)
			Engine::getInstance()->setTimeScale(static_cast<double>(args[0]));
	}

	void CommandNbrOfSystem(const std::vector<float>&)
	{
		std::cout << (std::to_string(Engine::getInstance()->getSystemSize())) << std::endl;
	}
}
