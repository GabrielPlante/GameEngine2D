#pragma once

#include "../GameEngine2D/Command.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {
	class CommandToggleGraphics :
		public ge::Command
	{
	public:
		//Constructor
		CommandToggleGraphics() : ge::Command{ "toggle_graphics" } {}

		//Execute the command
		void execute(const std::vector<float>&) override {
			if (F_FACTORY->gameComponent.graphicsOn)
				F_FACTORY->gameComponent.graphicsOn = false;
			else
				F_FACTORY->gameComponent.graphicsOn = true;
		}
	};
}
