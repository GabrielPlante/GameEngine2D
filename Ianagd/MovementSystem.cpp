#include "MovementSystem.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameEntity.h"
#include "PathFinder.h"
#include "GameCore.h"

namespace ian {
	//This function calculate a new position in a straight line between two point given certain speed
	ge::Vector2<double> move(ge::Vector2<> position, ge::Vector2<> destination, float speed) {
		double actualSpeed{ speed * ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(gv::speedDividingFactor) };
		ge::Angle movingAngle{ position.angle(destination) };

		ge::Vector2<double> newPosition{ static_cast<double>(position.x), static_cast<double>(position.y) };

		long destSign{ 1 };
		if (destination.x != position.x)
			destSign = static_cast<int>((destination.x - position.x) / std::abs(destination.x - position.x));
		if ((position.x + std::cos(movingAngle.get()) * actualSpeed) * destSign > destination.x * destSign) {
			newPosition = { static_cast<double>(destination.x), static_cast<double>(destination.y) };
		}
		else
			newPosition += ge::Vector2<double>{std::cos(movingAngle.get())* actualSpeed, std::sin(movingAngle.get())* actualSpeed};
		return newPosition;
	}

	//Special movement function for moving along the axis only
	ge::Vector2<double> moveAxis(ge::Vector2<double> position, std::stack<ge::Vector2<int>>* destinationStack, float speed) {
		double actualSpeed{ speed * ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(gv::speedDividingFactor) };

		while (actualSpeed != 0 && !destinationStack->empty()) {
			ge::Vector2<> currentDestination{ F_FACTORY->map.relativeToAbsolute(destinationStack->top()) };
			//Get the direction
			if (position.x != currentDestination.x) {
				//Is the entity going to reach it's next destination this frame
				if (abs(position.x - currentDestination.x) < actualSpeed) {
					actualSpeed -= abs(position.x - currentDestination.x);
					position.x = static_cast<double>(currentDestination.x);
					destinationStack->pop();
				}
				else {
					position.x += currentDestination.x > position.x ? actualSpeed : -actualSpeed;
					actualSpeed = 0;
				}
			}
			else {
				if (abs(position.y - currentDestination.y) < actualSpeed) {
					actualSpeed -= abs(position.y - currentDestination.y);
					position.y = currentDestination.y;
					destinationStack->pop();
				}
				else {
					position.y += currentDestination.y > position.y ? actualSpeed : -actualSpeed;
					actualSpeed = 0;
				}

			}
		}
		return position;
	}

	void MovementSystem::update() {
		//Update the simple movement
		for (auto it = F_FACTORY->movementFactory.getBeginningIterator(); it != F_FACTORY->movementFactory.getEndIterator(); it++) {
			if (it->isMoving) {
				ge::Vector2<double> newPosition{ move(F_FACTORY->positionFactory.getComponent(it->positionComponentId)->getPosition(), it->destination, it->speed) };
				if (newPosition == it->destination)
					it->isMoving = false;
				F_FACTORY->positionFactory.getComponent(it->positionComponentId)->setPosition(newPosition);
			}
		}
		//Update the more complex tile related movement
		for (auto it = F_FACTORY->tileMovementFactory.getBeginningIterator(); it != F_FACTORY->tileMovementFactory.getEndIterator(); it++) {
			if (it->isMoving) {
				ge::Vector2<double> newPosition{ moveAxis(F_FACTORY->positionFactory.getComponent(it->positionComponentId)->getDPosition(),
					&it->destinationStack, it->speed) };
				if (it->destinationStack.empty())
					it->isMoving = false;
				F_FACTORY->positionFactory.getComponent(it->positionComponentId)->setPosition(newPosition);
			}
		}
	}
}