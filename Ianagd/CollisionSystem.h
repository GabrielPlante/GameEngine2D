#pragma once

#include "../GameEngine2D/System.h"

namespace ian {
	class CollisionSystem
		: public ge::System
	{
	private:
	public:
		//Constructor
		CollisionSystem() {}

		//The update method, called each frame
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}

