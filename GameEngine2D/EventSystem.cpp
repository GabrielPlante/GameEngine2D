#include "EventSystem.h"
#include "Engine.h"

void EventSystem::update() {
	while (pollEvent()) {
		if (event.type == SDL_QUIT) {
			Engine::getInstance()->stop();
		}
	}

}
