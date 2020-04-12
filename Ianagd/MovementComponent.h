#pragma once
#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Component.h"

#include "GameEntity.h"

namespace ian {
	class MovementComponent
		: public ge::Component
	{
	public:
		//Needed to know the position
		GameEntity* owner;

		ge::Vector2<long> destination{ 0, 0 };

		float speed{ 0 };

		bool isMoving{ false };
	};
}