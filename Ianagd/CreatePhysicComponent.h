#pragma once

#include "../GameEngine2D/Message.h"
#include "../GameEngine2D/Position.h"
#include "Entity.h"

#include "MessageType.h"
#include "PhysicComponent.h"

namespace ian {
	class CreatePhysicComponent :
		public ge::Message
	{
	private:
		//Actual attribute
		PhysicComponent physicComponent;

		ge::Entity* entity;
	public:
		//Constructor
		CreatePhysicComponent(unsigned int messageOrigin, ge::Entity* entity, PhysicComponent physicComponent = PhysicComponent{})
			: ge::Message{ createPhysicComponent, messageOrigin }, entity{ entity }, physicComponent{ physicComponent }
		{}
		PhysicComponent getPhysicComponent() const {
			return physicComponent;
		}
	};

}
