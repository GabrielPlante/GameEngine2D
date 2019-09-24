#pragma once
#include <SDL.h>
#include <memory>

#include "System.h"

#include "EventHandler.h"


class EventSystem
{
private:
	static EventSystem* instance;

	//What event system is currently in use
	std::unique_ptr<EventHandler> currentEventHandler;

	SDL_Event event{ 0 };

	//Default constructor
	EventSystem();
public:
	//Initialise the singleton
	static void init();

	//Get the event system instance
	static EventSystem* getInstance() { return instance; }

	//Destroy the singleton
	static void quit();

	//What will update all component under this system control
	void update();

	void switchEventHandler(std::unique_ptr<EventHandler> eventHandler) { currentEventHandler = std::move(eventHandler); }
};

