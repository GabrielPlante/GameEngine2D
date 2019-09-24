#include "EventSystem.h"
#include "CommandList.h"
#include "ConsoleEventHandler.h"

#include "Console.h"

EventSystem* EventSystem::instance{ nullptr };

void EventSystem::init() {
	if (!instance) {
		instance = new EventSystem{};
	}
}

void EventSystem::quit() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

EventSystem::EventSystem() {
	currentEventHandler = std::unique_ptr<EventHandler>{ new ConsoleEventHandler() };
	CONSOLE_LOG("Event system successfully initialised");
}

void EventSystem::update() {
	std::unique_ptr<EventHandler> eventHandler = currentEventHandler->update(&event);

	if (eventHandler) {
		//If a new event handler take the control
		switchEventHandler(std::move(eventHandler));

		//Delete all other event
		while (SDL_PollEvent(&event)){}
	}
}
