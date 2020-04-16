#pragma once
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class MovementComponent
	{
	public:
		//Needed to know the position
		unsigned int positionComponentId;

		ge::Vector2<long> destination{ 0, 0 };

		float speed{ 0 };

		bool isMoving{ false };
	};
}