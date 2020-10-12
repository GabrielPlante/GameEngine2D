#pragma once

#include "../GameEngine2D/EventHandler.h"

namespace ian {
	class GameEventHandler
		: public ge::EventHandler
	{
	private:
	public:
		//Handle all the event
		void update(SDL_Event* event) override;

		//When this take the event control
		void takeControl() override {}

		//When this lose the event control
		void loseControl() override {}
	};

}
