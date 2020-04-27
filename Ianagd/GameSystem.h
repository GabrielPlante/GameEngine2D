#pragma once

#include "../GameEngine2D/System.h"

namespace ian {
	class GameSystem
		: public ge::System
	{
	private:
		int previousGold;

		unsigned int goldRendererId{ 0 };

		//Render the amount of gold the player have
		void renderGold(int amount);
	public:
		//Constructor
		GameSystem() {}

		//Update the game
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};

}
