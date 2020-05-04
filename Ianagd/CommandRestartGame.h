#pragma once

#include "../GameEngine2D/Command.h"

#include "GameCore.h"

namespace ian {
	class CommandRestartGame :
		public ge::Command
	{
	public:
		//Constructor
		CommandRestartGame() : ge::Command("restart_game") {}

		//Execute the command
		void execute(const std::vector<float>&) override {
			GameCore::getInstance()->restartGame();
		}
	};
}
