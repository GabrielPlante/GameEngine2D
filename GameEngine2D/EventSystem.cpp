#include "EventSystem.h"
#include "CommandList.h"
#include "ConsoleEventHandler.h"

#include "Console.h"

namespace ge {
	EventSystem::EventSystem() {
		pushEventHandler(std::unique_ptr<EventHandler>{ new ConsoleEventHandler() });
	}

	void EventSystem::update() {
		eventHandlerPile.back()->update(&event);
	}

	void EventSystem::pushEventHandler(std::unique_ptr<EventHandler> eventHandler) {
		eventHandlerPile.push_back(std::move(eventHandler));

		//Delete all other event
		while (SDL_PollEvent(&event)) {}
	}
}
