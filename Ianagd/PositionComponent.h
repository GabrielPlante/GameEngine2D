#pragma once
#include "../GameEngine2D/Component.h"
#include "../GameEngine2D/Position.h"

namespace ian {
	struct PositionComponent
		: public ge::Component
	{
		//The holded position
		ge::Position<float> position;
	};
}
