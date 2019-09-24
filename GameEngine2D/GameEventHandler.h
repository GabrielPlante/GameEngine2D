#pragma once
#include "EventHandler.h"
class GameEventHandler :
	public EventHandler
{
public:
	void update(SDL_Event* event) override;
};

