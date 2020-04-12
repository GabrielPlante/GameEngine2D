#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Console.h"

#include "GameCore.h"

namespace ian {
	class CommandZoom
		: public ge::Command
	{
	public:
		//Constructor
		CommandZoom()
			: Command("zoom")
		{}

		void execute(const std::vector<float>& args) override {
			if (args.size() > 1) {
				CONSOLE_LOG_ERROR("Error: wrong number of arguments. Expected: 0-1, got: " + std::to_string(args.size()))
			}
			else if (args.size() == 1)
				GameCore::getInstance()->getCamera()->zoom(args[0]);
			else
				//GameCore::getInstance()->getCamera()->resetZoom();
				CONSOLE_LOG(std::to_string(GameCore::getInstance()->getCamera()->getZoom()))
		}

	};
}
