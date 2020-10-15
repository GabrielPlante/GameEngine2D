#pragma once

#include "../Map/MapEntityComponent.h"

namespace ian {
	struct MovementComponent {
		MovementComponent(unsigned int mapEntityId, ge::Vector2<double> destination, ge::Vector2<double> position)
			: mapEntityId{ mapEntityId }, destination{ destination }, position{ position } {}

		//The id of the map entity component associated with this component
		unsigned int mapEntityId{ 0 };

		//The position of the component
		ge::Vector2<double> position;

		//The destination of this component
		ge::Vector2<double> destination;

		//Is the entity moving
		bool isMoving{ false };
	};
}
