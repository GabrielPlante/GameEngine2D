#pragma once
#include "Component.h"
#include "Position.h"
struct PhysicComponent
	:public Component
{
public:
	//The actual attribute are public because it's not the component that change them, it's the system
	Position<long> position;

	//Constructor
	PhysicComponent(const long ownerEntityID)
		:Component{ ownerEntityID }
	{}
};

