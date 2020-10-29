#pragma once
#include <stack>

#include "../Map/MapEntityComponent.h"

namespace ian {
	struct MovementComponent {
		MovementComponent(unsigned int mapEntityId, ge::Vector2<double> destination, ge::Vector2<double> position, unsigned int movespeed)
			: mapEntityId{ mapEntityId }, destination{ destination }, position{ position }, movespeed{ movespeed } {}

		//The id of the map entity component associated with this component
		unsigned int mapEntityId{ 0 };

		//The position of the component
		ge::Vector2<double> position;

		//The destination of this component
		ge::Vector2<double> destination;

		//The movespeed of the entity, in pixel per second
		unsigned int movespeed;

		std::stack<ge::Vector2<size_t>> destinationStack;
	};
}
