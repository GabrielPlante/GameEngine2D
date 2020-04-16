#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Console.h"

#include "GameCore.h"

namespace ian {
	class CommandEntityInfo
		: public ge::Command
	{
	public:
		//Constructor
		CommandEntityInfo() : ge::Command{ "entity_info" } {}

		void execute(const std::vector<float>& args) override {
			if (args.size() == 2) {
				CONSOLE_LOG(std::to_string(F_FACTORY->entityFactory.getComponent(static_cast<unsigned int>(args[0]))->getComponentId(static_cast<unsigned int>(args[1]))))
			}
		}
	};
}
