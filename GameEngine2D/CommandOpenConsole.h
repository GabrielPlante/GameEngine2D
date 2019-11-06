#pragma once
#include "Command.h"

#include "Engine.h"
#include "ConsoleEventHandler.h"

namespace ge {
	class CommandOpenConsole :
		public Command
	{
	public:
		//Constructor
		CommandOpenConsole()
			: Command("openconsole")
		{}

		//Execute the command
		void execute(const std::vector<float>&) override {
			if (!Console::getInstance()->isOpened())
				Engine::getInstance()->pushEventHandler(std::move(std::unique_ptr<EventHandler>{new ConsoleEventHandler{}}));
			else
				CONSOLE_LOG_ERROR("Error: Console already opened")
		}
	};
}
