#pragma once

#include "../GameEngine2D/Entity.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class EntityHandler
	{
	public:
		//Create an entity
		static unsigned int createEntity(ge::Vector2<double> position, unsigned int movespeed);

		//Set a destination for an entity
		static void setDestination(ge::Entity entityId, ge::Vector2<double> destination);
	};
}
