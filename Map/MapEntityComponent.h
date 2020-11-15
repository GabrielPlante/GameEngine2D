#pragma once

#include "../GameEngine2D/Vector2.h"

namespace map {
	//The component of an entity on the map
	struct MapEntityComponent
	{
		//The id of the component
		unsigned int id;

		//The entity position
		ge::Vector2<double> position;
	};
}
