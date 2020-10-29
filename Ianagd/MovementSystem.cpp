#include "MovementSystem.h"

#include "../GameEngine2D/Storage.h"
#include "../GameEngine2D/Engine.h"

#include "../Map/MapEntityHandler.h"
#include "../Map/HexagonalMap.h"

#include "MovementComponent.h"
#include "GameValues.h"

#include "../GameEngine2D/Console.h"

namespace ian {
	ge::Vector2<double> computeMove(ge::Vector2<double> position, ge::Vector2<double> destination, int movespeed) {
		//Get the time that passed since the last frame
		long long eludedTime{ ge::Engine::getInstance()->getTimeSinceLastFrame() };

		//The distance covered by the entity
		double distanceCovered{ static_cast<double>(eludedTime * movespeed / 1000.0 / 1000) };

		//The distance left to go for the entity
		double distanceLeftSquared{ position.distanceSquared(destination) };

		//The ratio distance left
		double ratioCovered{ distanceCovered / sqrt(distanceLeftSquared) };

		//If the entity if going to overshoot it's target, don't
		if (ratioCovered > 1) {
			ratioCovered = 1;
		}

		//The new position
		return ge::Vector2<double>{position.x + (destination.x - position.x) * ratioCovered, position.y + (destination.y - position.y) * ratioCovered};
	}

	void moveEntity(std::vector<MovementComponent>::iterator it) {
		ge::Vector2<double> newPosition{ computeMove(it->position, static_cast<ge::Vector2<double>>(map::HexagonalMap::relativeToAbsolute(it->destinationStack.top(), gv::tileWidth, gv::tileHeight)), it->movespeed) };

		//Move the entity in the map
		map::MapEntityHandler<gv::tileSize>::moveEntity(it->position, it->mapEntityId, newPosition);
		it->position = newPosition;

		//If we reached the next point of the stack, pop it
		if (newPosition == static_cast<ge::Vector2<double>>(map::HexagonalMap::relativeToAbsolute(it->destinationStack.top(), gv::tileWidth, gv::tileHeight)))
			it->destinationStack.pop();
	}

	void MovementSystem::update() {
		//For every movement component
		for (auto it = ge::Storage<MovementComponent>::begin(); it != ge::Storage<MovementComponent>::end(); it++) {
			//If it is moving
			if (!it->destinationStack.empty()) {
				//Move the entity
				moveEntity(it);
			}
		}
	}
}
