#include "PhysicSystem.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/Angle.h"
#include "../GameEngine2D/ComponentHandle.h"

#include "MessageType.h"

namespace ian {
	void PhysicSystem::update() {
		const float deltaTime{ static_cast<float>(ge::Engine::getInstance()->getTimeSinceLastFrame()) / 1000.0f };
		for (auto it = physicComponentFactory->getBeginningIterator(); it != physicComponentFactory->getEndIterator(); it++) {

			//If the entity need to move
			if (it->positionComponent->position != it->destination) {
				//Store the distance the entity can go since the last frame
				const float deltaMovement{ it->speed * deltaTime };

				//If the entity is arriving at it's positionComponent->position this frame, put it at it's destination
				if (it->positionComponent->position.distanceSquared(it->destination) < it->speed * it->speed) {
					it->positionComponent->position = it->destination;
				}
				//Else move the entity according to it's speed and direction
				else {
					const ge::Angle destinationAngle{ it->positionComponent->position.angle(it->destination) };
					it->positionComponent->position.x += static_cast<float>(-sin(destinationAngle.get()) * deltaMovement);
					it->positionComponent->position.y += static_cast<float>(cos(destinationAngle.get()) * deltaMovement);
				}
			}
		}
	}

	void PhysicSystem::handleMessage(std::shared_ptr<ge::Message> message) {
	}
}
