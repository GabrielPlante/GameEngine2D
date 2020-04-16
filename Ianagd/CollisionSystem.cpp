#include "CollisionSystem.h"

#include "GameCore.h"

namespace ian {
	void CollisionSystem::update() {
		//Naive collision system implementation, in O(n^2), with n the number of collision component
		//Could be greatly improved if needed by making a grid of object and updating it every time an object move
		for (auto it = F_FACTORY->collisionFactory.getBeginningIterator(); it != F_FACTORY->collisionFactory.getEndIterator(); it++) {
			for (auto iti = it++; iti != F_FACTORY->collisionFactory.getEndIterator(); iti++) {
				if (pow(it->size - iti->size, 2) <= F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.distanceSquared(F_FACTORY->positionFactory.getComponent(iti->positionComponentId)->position)
					&& F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.distanceSquared(F_FACTORY->positionFactory.getComponent(iti->positionComponentId)->position) <= pow(it->size + iti->size, 2)) {
					//Handle the collision
				}
			}
		}
	}
}
