#pragma once
#include <vector>

#include "../GameEngine2D/Position.h"
#include "../GameEngine2D/Component.h"

#include "PositionComponent.h"

namespace ian {
	/// <summary>
	/// This component hold everything needed for the physic engine to work on the physic of an entity
	/// </summary>
	struct PhysicComponent
		: public ge::Component
	{
		//No default constructor because a pointer to a position component is needed
		PhysicComponent(PositionComponent* positionComponent) : positionComponent{ positionComponent } {}

		//The actual position of the entity
		PositionComponent* positionComponent;

		//For the begining, the destination is only a position
		ge::Position<float> destination{ 0, 0 };

		//The speed of the entity
		float speed{ 0 };
	};

	//Overloading the << operator for a vector for a quick load in the vector
	//void operator<<(std::vector<float>& vector, const PhysicComponent& physicComponent);

	//Overloading the << operator for a vector for a quick unload in the vector
	//void operator>>(std::vector<float>& vector, PhysicComponent& physicComponent);

}

