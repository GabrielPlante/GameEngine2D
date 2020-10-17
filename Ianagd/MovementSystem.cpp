#include "MovementSystem.h"

#include "../GameEngine2D/Storage.h"
#include "../GameEngine2D/Engine.h"

#include "../Map/MapEntityHandler.h"

#include "MovementComponent.h"
#include "GameValues.h"

#include "../GameEngine2D/Console.h"
#include <iostream>

namespace ian {
	void moveEntity(std::vector<MovementComponent>::iterator it) {
		//Get the time that passed since the last frame
		long long eludedTime{ ge::Engine::getInstance()->getTimeSinceLastFrame() };

		//The distance covered by the entity
		double distanceCovered{ static_cast<double>(eludedTime * it->movespeed / 1000.0 / 1000) };

		//The distance left to go for the entity
		double distanceLeftSquared{ it->position.distanceSquared(it->destination) };

		//The ratio distance left
		double ratioCovered{ distanceCovered / sqrt(distanceLeftSquared) };

		//If the entity if going to overshoot it's target, don't
		if (ratioCovered > 1) {
			ratioCovered = 1;
			it->isMoving = false;
		}

		//The new position
		ge::Vector2<double> newPosition{ it->position.x + (it->destination.x - it->position.x) * ratioCovered, it->position.y + (it->destination.y - it->position.y) * ratioCovered };

		//Move the entity in the map
		map::MapEntityHandler<gv::tileSize>::moveEntity(it->position, it->mapEntityId, newPosition);
		it->position = newPosition;
	}

	void MovementSystem::update() {
		//For every movement component
		for (auto it = ge::Storage<MovementComponent>::begin(); it != ge::Storage<MovementComponent>::end(); it++) {
			//If it is moving
			if (it->isMoving) {
				//Move the entity
				moveEntity(it);
			}
		}
	}
}
