#pragma once
#include "Position.h"
#include "Handle.h"

class EntityMovementComponent
{
private:
	Handle handle;
public:
	Position<long> position;

	//Constructor
	EntityMovementComponent( Handle handle, Position<long> position )
		: handle{ handle }, position{ position }
	{}
};
