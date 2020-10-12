#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Engine.h"

#include "GameEventHandler.h"

namespace ian {
	class CommandQuitConsole
		: public ge::Command
	{
	private:
	public:
		//Constructor
		CommandQuitConsole()
			: Command{ "quitconsole" }
		{}

		//Execute
		void execute(const std::vector<float>&) override {
			//If only the console is in the event handler pile
			if (ge::Engine::getInstance()->getEventHandlerPileSize() == 1)
				ge::Engine::getInstance()->pushEventHandler(std::move(std::unique_ptr<ge::EventHandler>{new GameEventHandler{}}));
			else
				ge::Engine::getInstance()->popEventHandler();
		}
	};
}
