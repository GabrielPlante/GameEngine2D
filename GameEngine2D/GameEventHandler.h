#pragma once
#include "EventHandler.h"
class GameEventHandler :
	public EventHandler
{
public:
	std::unique_ptr<EventHandler> update(SDL_Event* event) override;
};

