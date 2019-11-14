#include "PhysicSystem.h"

#include "..//GameEngine2D/Engine.h"
#include "../GameEngine2D/Angle.h"
#include "../GameEngine2D/ComponentHandle.h"

#include "MessageType.h"
#include "CreatePhysicComponent.h"

namespace ian {
	void PhysicSystem::update() {
		const float deltaTime{ static_cast<float>(ge::Engine::getInstance()->getTimeSinceLastFrame()) / 1000.0f };
		for (auto it = physicComponentFactory.getBeginningIterator(); it != physicComponentFactory.getEndIterator(); it++) {

			//If the entity need to move
			if (it->position != it->destination) {
				//Store the distance the entity can go since the last frame
				const float deltaMovement{ it->speed * deltaTime };

				//If the entity is arriving at it's position this frame, put it at it's destination
				if (it->position.distanceSquared(it->destination) < it->speed * it->speed) {
					it->position = it->destination;
				}
				//Else move the entity according to it's speed and direction
				else {
					const ge::Angle destinationAngle{ it->position.angle(it->destination) };
					it->position.x += static_cast<float>(-sin(destinationAngle.get()) * deltaMovement);
					it->position.y += static_cast<float>(cos(destinationAngle.get()) * deltaMovement);
				}
			}
		}
	}

	void PhysicSystem::handleMessage(std::shared_ptr<ge::Message> message) {
		//If the message is a create physic component message
		if (message->getMessageType() == createPhysicComponent) {
			//Cast the message in it's proper form
			std::shared_ptr<CreatePhysicComponent> newPhysicComponent{ std::static_pointer_cast<CreatePhysicComponent>(message) };
			unsigned int componentId{ physicComponentFactory.addComponent(newPhysicComponent->getComponent()) };

			//Callback the entity
			newPhysicComponent->sendBackHandle(ge::ComponentHandle{ componentId, this });

			//Extract the component from the message data
			/*PhysicComponent component;
			message->messageData >> component;*/
			
		}
	}
}
