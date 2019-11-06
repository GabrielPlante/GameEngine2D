#include "EventSystem.h"
#include "CommandList.h"
#include "Console.h"

namespace ge {

	void EventSystem::update() {
		eventHandlerPile.back()->update(&event);
	}

	void EventSystem::pushEventHandler(std::unique_ptr<EventHandler> eventHandler) {

		if (!eventHandlerPile.empty()) {
			//Inform the current event handler that it is going to lose the control
			eventHandlerPile.back()->loseControl();
		}

		eventHandlerPile.push_back(std::move(eventHandler));

		//Inform the new event handler that it took control
		eventHandlerPile.back()->takeControl();

		//Delete all other event
		while (SDL_PollEvent(&event)) {}

	}

	void EventSystem::popEventHandler() {
		if (eventHandlerPile.size() > 1) {
			//Inform the current event handler that it is going to lose the control
			eventHandlerPile.back()->loseControl();

			eventHandlerPile.pop_back();

			//Inform the new event handler that it took control
			eventHandlerPile.back()->takeControl();
		}
		else {
			CONSOLE_LOG_ERROR("Error: tried to pop the event handler pile with only one event handler left")
		}
	}
}
