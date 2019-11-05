#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Factory.h"

#include "PhysicComponent.h"

namespace ian {
	class PhysicSystem
		: public ge::System
	{
	private:
		ge::Factory<PhysicComponent> physicComponentFactory;
	public:
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}
