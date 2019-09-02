#pragma once
#include <vector>

#include "PhysicComponent.h"

class PhysicComponentFactory
{
private:
	std::vector<PhysicComponent> physicComponentList;
public:
	//Add a physic component to the list 
	void addPhysicComponent(const long ownerEntityID) { physicComponentList.push_back(PhysicComponent{ ownerEntityID }); }

	//std::iterator<std::vector<PhysicComponent>, > 
};

