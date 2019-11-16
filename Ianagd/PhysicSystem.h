#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Factory.h"

#include "PhysicComponent.h"

namespace ian {
	class PhysicSystem
		: public ge::System
	{
	private:
		//Pointer to the physic component factory
		ge::Factory<PhysicComponent>* physicComponentFactory;
	public:
		//Constructor
		PhysicSystem(ge::Factory<PhysicComponent>* physicComponentFactory) : physicComponentFactory{ physicComponentFactory } {}

		//Update the physic system, go through all the component and update them
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override;
	};
}
