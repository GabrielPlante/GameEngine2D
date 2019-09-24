#pragma once
#include "EventHandler.h"
class ConsoleEventHandler :
	public EventHandler
{
public:
	//Update the console
	std::unique_ptr<EventHandler> update(SDL_Event* event) override;
};

