#pragma once
#include "../GameEngine2D/Message.h"
#include "../GameEngine2D/ComponentHandle.h"
#include "../GameEngine2D/Entity.h"

#include "PhysicComponent.h"
#include "MessageType.h"

namespace ian {

	class CreatePhysicComponent :
		public ge::Message
	{
	private:
		ge::Entity* entityPtr;
		PhysicComponent component;
	public:
		//Constructor
		CreatePhysicComponent(unsigned int messageOrigin, PhysicComponent&& component, ge::Entity* creatorPtr) 
			: Message{ createPhysicComponent, messageOrigin }, component{ component }, entityPtr{ creatorPtr }
		{}

		//Get the physic component the entity wanted to create
		const PhysicComponent& getComponent() const { return component; }

		void sendBackHandle(ge::ComponentHandle&& componentHandle) const;
	};

}
