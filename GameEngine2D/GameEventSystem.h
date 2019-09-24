#pragma once
#include "EventHandler.h"

class GameEventHandler :
	public EventHandler
{
public:
	//Default constructor
	GameEventSystem() {}

	//Handle all the event while in the game
	void update(SDL_Event* event) override;
};

