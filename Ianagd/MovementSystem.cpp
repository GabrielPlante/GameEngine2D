#include "MovementSystem.h"

#include "../GameEngine2D/Engine.h"

#include "GameValues.h"
#include "GameEntity.h"
#include "GameCore.h"

namespace ian {
	void MovementSystem::update() {
		for (auto it = F_FACTORY->movementFactory.getBeginningIterator(); it != F_FACTORY->movementFactory.getEndIterator(); it++) {
			if (it->isMoving) {
				double actualSpeed{ ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(speedDividingFactor) };

				ge::Angle movingAngle{ F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.angle(it->destination) };
				long destSign{ 1 };
				if (it->destination.x != F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.x)
					destSign = static_cast<int>((it->destination.x - F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.x) / std::abs(it->destination.x - F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.x));
				if ((F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position.x + std::cos(movingAngle.get()) * actualSpeed) * destSign > it->destination.x * destSign) {
					F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position = it->destination;
					it->isMoving = false;
				}
				else {
					F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position += ge::Vector2<>{
						static_cast<long>(std::cos(movingAngle.get())* actualSpeed),
							static_cast<long>(std::sin(movingAngle.get())* actualSpeed)};
				}
			}
		}
	}

	void MovementSystem::setDestination(unsigned int componentId, ge::Vector2<> destination) {
		F_FACTORY->movementFactory.getComponent(componentId)->destination = destination;
		F_FACTORY->movementFactory.getComponent(componentId)->isMoving = true;
	}
}