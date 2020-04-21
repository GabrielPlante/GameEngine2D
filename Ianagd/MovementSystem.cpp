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
	ge::Vector2<> move(ge::Vector2<> position, ge::Vector2<> destination, float speed) {
		double actualSpeed{ speed * ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(speedDividingFactor) };
		ge::Angle movingAngle{ position.angle(destination) };

		long destSign{ 1 };
		if (destination.x != position.x)
			destSign = static_cast<int>((destination.x - position.x) / std::abs(destination.x - position.x));
		if ((position.x + std::cos(movingAngle.get()) * actualSpeed) * destSign > destination.x * destSign) {
			position = destination;
		}
		else
			position += ge::Vector2<>{static_cast<long>(std::cos(movingAngle.get())* actualSpeed), static_cast<long>(std::sin(movingAngle.get())* actualSpeed)};
		return position;
	}

	//Special movement function for moving along the axis only
	ge::Vector2<> moveAxis(ge::Vector2<> position, std::stack<ge::Vector2<int>>* destinationStack, float speed) {
		long actualSpeed{ static_cast<long>(speed * ge::Engine::getInstance()->getTimeSinceLastFrame() / static_cast<double>(speedDividingFactor)) };
		while (actualSpeed != 0 && !destinationStack->empty()) {
			ge::Vector2<> currentDestination{ F_FACTORY->map.relativeToAbsolute(destinationStack->top()) };
			//Get the direction
			if (position.x != currentDestination.x) {
				//Is the entity going to reach it's next destination this frame
				if (abs(position.x - currentDestination.x) < actualSpeed) {
					actualSpeed -= abs(position.x - currentDestination.x);
					position.x = currentDestination.x;
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
				ge::Vector2<> newPosition{ move(F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position, it->destination, it->speed) };
				if (newPosition == it->destination)
					it->isMoving = false;
				F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position = newPosition;
			}
		}
		//Update the more complex tile related movement
		for (auto it = F_FACTORY->tileMovementFactory.getBeginningIterator(); it != F_FACTORY->tileMovementFactory.getEndIterator(); it++) {
			if (it->isMoving) {
				ge::Vector2<> newPosition{ moveAxis(F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position,
					&it->destinationStack, it->speed) };
				if (it->destinationStack.empty())
					it->isMoving = false;
				F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position = newPosition;
			}
		}
	}

	void MovementSystem::setDestination(unsigned int componentId, ge::Vector2<> destination, bool tileMovement) {
		if (!tileMovement) {
			F_FACTORY->movementFactory.getComponent(componentId)->destination = destination;
			F_FACTORY->movementFactory.getComponent(componentId)->isMoving = true;
		}
		else {
			ge::Vector2<> entityPos{ F_FACTORY->positionFactory.getComponent(F_FACTORY->tileMovementFactory.getComponent(componentId)->positionComponentId)->position };
			PathFinder pathFinder{ F_FACTORY->map.absoluteToRelative(entityPos), F_FACTORY->map.absoluteToRelative(destination) };
			std::stack<ge::Vector2<int>> pathStack{ pathFinder.findPath() };
			if (!pathStack.empty()) {
				F_FACTORY->tileMovementFactory.getComponent(componentId)->destinationStack = pathStack;
				F_FACTORY->tileMovementFactory.getComponent(componentId)->isMoving = true;
			}
		}
	}
}