#include "EventSystem.h"
#include "CommandList.h"
#include "GameEventHandler.h"
#include "ConsoleEventHandler.h"

EventSystem::EventSystem() {
	if (currentEventHandler.get() == nullptr)
		currentEventHandler = std::unique_ptr<EventHandler>{ new GameEventHandler() };
}

void EventSystem::update() {
	currentEventHandler->update(&event);
}
