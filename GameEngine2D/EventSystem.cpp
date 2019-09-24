#include "EventSystem.h"
#include "CommandList.h"
#include "GameEventHandler.h"
#include "ConsoleEventHandler.h"

EventSystem::EventSystem() {
	if (currentEventHandler.get() == nullptr)
		currentEventHandler = std::unique_ptr<EventHandler>{ new GameEventHandler() };
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
