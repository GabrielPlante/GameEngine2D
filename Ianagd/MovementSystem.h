#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class MovementSystem
		: public ge::System
	{
	private:

	public:
		//Constructor
		MovementSystem() {}

		//The update method, called each frame
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};

		//Set a destination for a component
		void setDestination(unsigned int componentId, ge::Vector2<> destination, bool tileMovement = false);
	};
}

