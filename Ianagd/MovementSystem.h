#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Factory.h"

#include "MovementComponent.h"

namespace ian {
	class MovementSystem
		: public ge::System
	{
	private:
		ge::Factory<MovementComponent>* movementComponentFactory;
	public:
		//Constructor
		MovementSystem(ge::Factory<MovementComponent>* movementComponentFactory);

		//The update method, called each frame
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};

		//Set a destination for a component
		void setDestination(unsigned int componentId, ge::Vector2<> destination);

		//Create a movement component for an entity
		void createMovementComponent(GameEntity* gameEntity) const;
	};
}

