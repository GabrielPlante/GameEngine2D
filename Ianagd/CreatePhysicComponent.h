#pragma once

#include "../GameEngine2D/Message.h"
#include "../GameEngine2D/Position.h"

#include "MessageType.h"
#include "PhysicComponent.h"

namespace ian {
	class CreatePhysicComponent :
		public ge::Message
	{
	public:
		//Actual attribute
		ge::Position<float> position;
		ge::Position<float> destination;
		float speed;

		//Constructor
		CreatePhysicComponent(unsigned int messageOrigin, ge::Position<float> position = ge::Position<float>{ 0, 0 },
			ge::Position<float> destination = ge::Position<float>{ 0, 0 }, float speed = 0)
			: ge::Message{ createPhysicComponent, messageOrigin }, position{ position }, destination{ destination }, speed{ speed }
		{}

		PhysicComponent getPhysicComponent() const {
			PhysicComponent component;
			component.position = position;
			component.destination = destination;
			component.speed = speed;
			return component;
		}
	};

}
