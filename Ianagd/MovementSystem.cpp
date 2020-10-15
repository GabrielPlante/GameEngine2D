#include "MovementSystem.h"

#include "../GameEngine2D/Storage.h"
#include "../GameEngine2D/Engine.h"

#include "MovementComponent.h"

namespace ian {
	void MovementSystem::update() {
		//For every movement component
		/*for (auto it = ge::Storage<MovementComponent>::begin(); it != ge::Storage<MovementComponent>::end(); it++) {
			//If it is moving
			if (it->isMoving) {
				//Get the time that passed since the last frame
				long long eludedTime{ ge::Engine::getInstance()->getTimeSinceLastFrame() };
				//ge::Vector2<double>
			}
		}*/
	}
}
