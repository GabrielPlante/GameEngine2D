#include "MovementSystem.h"

#include "../GameEngine2D/Engine.h"

#include "GameValues.h"
#include "GameEntity.h"
#include "GameCore.h"

namespace ian {
	void MovementSystem::update() {
		for (auto it = F_FACTORY->movementComponentFactory.getBeginningIterator(); it != F_FACTORY->movementComponentFactory.getEndIterator(); it++) {
			if (it->isMoving) {
				double actualSpeed{ ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(speedDividingFactor) };

				ge::Angle movingAngle{ F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().angle(it->destination) };
				int destSign{ 1 };
				if (it->destination.x != F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().x)
					destSign = static_cast<int>((it->destination.x - F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().x) / std::abs(it->destination.x - F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().x));
				if ((F_FACTORY->entityFactory.getComponent(it->ownerId)->getPosition().x + std::cos(movingAngle.get()) * actualSpeed) * destSign > it->destination.x * destSign) {
					F_FACTORY->entityFactory.getComponent(it->ownerId)->setPosition(it->destination);
					it->isMoving = false;
				}
				else {
					F_FACTORY->entityFactory.getComponent(it->ownerId)->changePosition(ge::Vector2<>{
						static_cast<long>(std::cos(movingAngle.get())* actualSpeed),
							static_cast<long>(std::sin(movingAngle.get())* actualSpeed)});
				}
			}
		}
	}

	void MovementSystem::setDestination(unsigned int componentId, ge::Vector2<> destination) {
		F_FACTORY->movementComponentFactory.getComponent(componentId)->destination = destination;
		F_FACTORY->movementComponentFactory.getComponent(componentId)->isMoving = true;
	}

	void MovementSystem::createMovementComponent(GameEntity* gameEntity) const {
		MovementComponent movementComponent;
		gameEntity->addControlComponentId(0, F_FACTORY->movementComponentFactory.addComponent(std::move(movementComponent)));
	}
}