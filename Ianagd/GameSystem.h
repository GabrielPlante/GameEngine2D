#pragma once

#include "../GameEngine2D/System.h"

namespace ian {
	class GameSystem
		: public ge::System
	{
	public:
		//Constructor
		GameSystem() {}

		//Update the game
		void update() override {}

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};

}
