#pragma once

#include "../GameEngine2D/Position.h"

namespace ian {	
	/// <summary>
	/// This component hold everything needed for the physic engine to work on the physic of an entity
	/// </summary>
	struct PhysicComponent
	{
		//The actual position of the entity
		ge::Position<float> position;

		//For the begining, the destination is only a position
		ge::Position<float> destination;

		//The speed of the entity
		float speed;
	};
}

