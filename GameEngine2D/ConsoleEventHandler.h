#pragma once
#include "EventHandler.h"
class ConsoleEventHandler :
	public EventHandler
{
public:
	void update(SDL_Event* event) override;
};

