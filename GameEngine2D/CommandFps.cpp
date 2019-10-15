#include "CommandFps.h"

#include "Console.h"
#include "Engine.h"

constexpr int FPS_MIN{ 10 };

namespace ge {
	void CommandFps::execute(const std::vector<float>& args) {
		if (args.empty()) {
			CONSOLE_LOG("FPS " + std::to_string(1 / (static_cast<double>(Engine::getInstance()->getTimeBetweenFrame()) / 1000.0)));
		}
		else {
			if (args[0] > FPS_MIN)
				Engine::getInstance()->setTimeBetweenFrame(static_cast<unsigned int>(1000/args[0]));
		}
	}
}