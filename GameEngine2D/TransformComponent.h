#pragma once

#include "Vector2.h"

namespace ge {
	//A transform component is associated with every entity, it represent it's position
	struct TransformComponent {
		//The entity position
		ge::Vector2<double> position{ 0, 0 };

		//The entity orientation
		double orientation{ 0 };
	};
}
