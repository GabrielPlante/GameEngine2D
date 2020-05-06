#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Console.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	class CommandStartNewWave :
		public ge::Command
	{
	public:
		//Constructor
		CommandStartNewWave() : ge::Command{ "start_new_wave" } {}

		//Execute the command
		void execute(const std::vector<float>&) override {
			if (F_FACTORY->gameComponent.startNewWave == interWave) {
				F_FACTORY->gameComponent.startNewWave = goForNextWave;
				if (F_FACTORY->gameComponent.graphicsOn) {
					F_FACTORY->positionFactory.getComponent(F_FACTORY->uiFactory.getComponent(F_FACTORY->gameComponent.starterUiId)->positionComponentId)
						->setPosition(ge::Vector2<>{0, -gv::tileSize * 2});
				}
			}
			else
				CONSOLE_LOG_ERROR("You can't start a new wave when you aren't between wave")
		}
	};
}
