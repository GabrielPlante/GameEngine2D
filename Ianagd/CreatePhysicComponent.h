#pragma once
#include "../GameEngine2D/Message.h"
#include "../GameEngine2D/ComponentHandle.h"

#include "PhysicComponent.h"
#include "MessageType.h"

namespace ian {
	class Entity;

	class CreatePhysicComponent :
		public ge::Message
	{
	private:
		Entity* entityPtr;
		PhysicComponent component;
	public:
		//Constructor
		CreatePhysicComponent(unsigned int messageOrigin, PhysicComponent&& component, Entity* creatorPtr) 
			: Message{ createPhysicComponent, messageOrigin }, component{ component }, entityPtr{ creatorPtr }
		{}

		//Get the physic component the entity wanted to create
		const PhysicComponent& getComponent() const { return component; }

		void sendBackHandle(ge::ComponentHandle&& componentHandle) const;
	};

}
