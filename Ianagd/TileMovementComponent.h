#pragma once
#include <stack>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class TileMovementComponent
	{
	public:
		//Needed to know the position
		unsigned int positionComponentId;

		std::stack<ge::Vector2<int>> destinationStack;

		float speed{ 1 };

		bool isMoving{ false };
	};
}
