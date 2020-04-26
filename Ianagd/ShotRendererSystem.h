#pragma once

#include "../GameEngine2D/System.h"

namespace ian {
	class ShotRendererSystem
		:public ge::System
	{
	public:
		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}

