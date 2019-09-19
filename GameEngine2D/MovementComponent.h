#pragma once
#include <vector>
#include <memory>

#include "Position.h"

struct MovementComponent
{
	//The actual position of the component
	Position<float> position;
	//The destination of the component
	Position<long> destination;
	//The list of the future destination once it have reached the actual destination
	std::unique_ptr<std::vector<Position<long>>> destinationList;
	//Is the component moving
	bool isMoving{ false };

	//The direction the component is actually facing
	Angle facingDirection;
	//The angle the component is turning to
	Angle facingDirectionDestination;
	//Is the component rotating
	bool isRotating{ false };
};
