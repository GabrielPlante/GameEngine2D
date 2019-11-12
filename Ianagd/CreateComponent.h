#pragma once

#include "../GameEngine2D/Message.h"
#include "../GameEngine2D/Entity.h"

namespace ian {
	template <typename Component>
	class CreateComponent
		: public ge::Message
	{
	private:
		//A pointer to the entity
		ge::Entity* entity;

		//The component that need created
		Component component;

	public:
		//Constructor
		CreateComponent<T>(unsigned int messageType, unsigned int messageOrigin, ge::Entity* entity, const Component& component)
			: ge::Message{ messageType, messageOrigin }, entity{ entity }, component{ component }
		{}

		//Get the component of the class
		Component getComponent() const { return Component; }

		//Get the pointer to the entity that want to create this component
		ge::Entity* entity getEntity() const { return entity; }
	};
}
