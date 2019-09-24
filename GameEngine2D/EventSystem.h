#pragma once
#include <SDL.h>
#include <memory>

#include "System.h"

#include "EventHandler.h"


class EventSystem :
	public System
{
private:
	//What event system is currently in use
	std::unique_ptr<EventHandler> currentEventHandler;
protected:
	SDL_Event event{ 0 };

public:
	//Default constructor
	EventSystem();

	//What will update all component under this system control
	void update() override;

	void switchEventSystem(std::unique_ptr<EventHandler> eventHandler) { currentEventHandler = std::move(eventHandler); }
};

