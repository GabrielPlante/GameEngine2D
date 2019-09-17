#pragma once
#include <vector>

#include "IDGenerator.h"

/*
 * Factory is the template class that will hold every component of a component type
 * The id given after adding a component is garanted not to change
*/
template <typename Component>
class Factory
{
private:
	IDGenerator<> iDGenerator;
	std::vector<Component> componentList;
public:
	//Add a component to the list, and return an id for the component
	int addComponent(Component component) {
		componentList.push_back(component);
		return iDGenerator.getNewID();
	}
	
	//TODO add the delete component method
};

