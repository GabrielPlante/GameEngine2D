#pragma once

#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Entity.h"

namespace ian {
	class EntityHandler
	{
	public:
		//Create an entity
		static ge::Entity createEntity(ge::Vector2<double> position, unsigned int movespeed);

		//Set a destination for an entity
		static void setDestination(ge::Entity entityId, ge::Vector2<double> destination);
	};
}
