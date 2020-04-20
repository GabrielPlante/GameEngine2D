#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Console.h"

#include "../GameEngine2D/Camera.h"

#include "GameCore.h"

namespace ian {
	class CommandResetZoom
		: public ge::Command
	{
	public:
		//Constructor
		CommandResetZoom()
			: Command("reset_zoom")
		{}

		void execute(const std::vector<float>& args) override {
			if (args.size() > 1) {
				CONSOLE_LOG_ERROR("Error: wrong number of arguments. Expected: 0-1, got: " + std::to_string(args.size()))
			}
			else if (args.size() == 1) {
				GameCore::getInstance()->getCamera()->resetZoom();
				GameCore::getInstance()->getCamera()->zoom(args[0]);
			}
			else
				GameCore::getInstance()->getCamera()->resetZoom();
		}

	};
}
