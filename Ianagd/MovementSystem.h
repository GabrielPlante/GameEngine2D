#pragma once
#include "..\GameEngine2D\System.h"

namespace ian {
	class MovementSystem :
		public ge::System
	{
	public:
		//What will update all component under this system control
		void update() override;

		//As a subscriber, a system need to be able to handle a message
		//void handleMessage(std::shared_ptr<Message> message) override {}
	};
}
