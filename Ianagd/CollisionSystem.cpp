#include "CollisionSystem.h"

#include "GameCore.h"

namespace ian {
	void CollisionSystem::update() {
		//Naive collision system implementation, in O(n^2), with n the number of collision component
		//Could be greatly improved if needed by making a grid of object and updating it every time an object move
		for (auto it = F_FACTORY->collisionComponentFactory.getBeginningIterator(); it != F_FACTORY->collisionComponentFactory.getEndIterator(); it++) {
			for (auto iti = it++; iti != F_FACTORY->collisionComponentFactory.getEndIterator(); iti++) {
				if (pow(it->size - iti->size, 2) <= F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().distanceSquared(F_FACTORY->entityFactory.getComponent(iti->ownerId)->getPosition())
					&& F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().distanceSquared(F_FACTORY->entityFactory.getComponent(iti->ownerId)->getPosition()) <= pow(it->size + iti->size, 2)) {
					//Handle the collision
				}
			}
		}
	}
}
