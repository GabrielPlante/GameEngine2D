#pragma once
#include "../GameEngine2D/EventHandler.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class GameEventHandler :
		public ge::EventHandler
	{
	private: 
		ge::Vector2<int> cameraMovement;

		int towerSelected{ -1 };

		unsigned int towerSelId{ 0 };
		unsigned int towerRangeId{ 0 };

		//Handle the tower selected ui
		void handleTowSelUi();
	public:
		//Handle all the event
		void update(SDL_Event* event) override;

		//When this take the event control
		void takeControl() override {}

		//When this lose the event control
		void loseControl() override {}
	};
}

