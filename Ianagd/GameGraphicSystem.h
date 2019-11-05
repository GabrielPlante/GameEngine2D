#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Window.h"

namespace ian {
	
	/// <summary>
	/// The grapic system of the game
	/// </summary>
	/// <seealso cref="ge::System" />
	class GameGraphicSystem :
		public ge::System
	{
	private:
		ge::Window window;
	public:
		//Constructor
		GameGraphicSystem(int screenWidth, int screenHeight);

		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}

