#include "MovementSystem.h"

#include "../GameEngine2D/Engine.h"

#include "GameValues.h"
#include "GameEntity.h"

namespace ian {
	MovementSystem::MovementSystem(ge::Factory<MovementComponent>* movementComponentFactory)
		: movementComponentFactory{ movementComponentFactory }
	{}

	void MovementSystem::update() {
		for (auto it = movementComponentFactory->getBeginningIterator(); it != movementComponentFactory->getEndIterator(); it++) {
			if (it->isMoving) {
				double actualSpeed{ ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(speedDividingFactor) };

				ge::Angle movingAngle{ it->owner->getPosition().angle(it->destination) };
				int destSign{ 1 };
				if (it->destination.x != it->owner->getPosition().x)
					destSign = static_cast<int>((it->destination.x - it->owner->getPosition().x) / std::abs(it->destination.x - it->owner->getPosition().x));
				if ((it->owner->getPosition().x + std::cos(movingAngle.get()) * actualSpeed) * destSign > it->destination.x * destSign) {
					it->owner->setPosition(it->destination);
					it->isMoving = false;
				}
				else {
					it->owner->changePosition(ge::Vector2<>{
						static_cast<long>(std::cos(movingAngle.get())* actualSpeed),
							static_cast<long>(std::sin(movingAngle.get())* actualSpeed)});
				}
			}
		}
	}

	void MovementSystem::setDestination(unsigned int componentId, ge::Vector2<> destination) {
		movementComponentFactory->getComponent(componentId)->destination = destination;
		movementComponentFactory->getComponent(componentId)->isMoving = true;
	}

	void MovementSystem::createMovementComponent(GameEntity* gameEntity) const {
		MovementComponent movementComponent;
		gameEntity->addControlComponentId(0, movementComponentFactory->addComponent(std::move(movementComponent)));
	}
}