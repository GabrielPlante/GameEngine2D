#pragma once
#include "EventHandler.h"
class ConsoleEventHandler :
	public EventHandler
{
public:
	std::unique_ptr<EventHandler> update(SDL_Event* event) override;
};

