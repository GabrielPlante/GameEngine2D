#include "EventSystem.h"
#include "CommandList.h"

#include <iostream>

namespace ge {

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
			std::cout << ("Error: tried to pop the last event handler of the pile") << std::endl;
		}
	}
}
