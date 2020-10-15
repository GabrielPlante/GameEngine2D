#pragma once

#include "../GameEngine2D/Vector2.h"

namespace map {
	//The component of an entity on the map
	struct MapEntityComponent
	{
		MapEntityComponent(unsigned int id, ge::Vector2<double> position)
			: id{ id }, position{ position } {}

		//The id of the component
		unsigned int id;

		//The entity position
		ge::Vector2<double> position;
	};
}
