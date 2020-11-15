#pragma once
#include <stack>

#include "../Map/MapEntityComponent.h"

namespace ian {
	struct MovementComponent {
		//The destination of this component
		ge::Vector2<double> destination;

		//The movespeed of the entity, in pixel per second
		unsigned int movespeed;

		std::stack<ge::Vector2<size_t>> destinationStack;
	};
}
