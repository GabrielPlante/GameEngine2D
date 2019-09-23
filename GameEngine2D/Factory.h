#pragma once
#include <vector>
#include <unordered_map>

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
	std::unordered_map<unsigned int, unsigned int> iDtoPlace;
public:
	//Add a component to the list, and return an id for the component
	unsigned int addComponent(Component component);

	Component* getComponent(unsigned long id) { return &componentList[iDtoPlace.find(id)->second]; }

	typename std::vector<Component>::iterator getBeginningIterator() { return componentList.begin(); }
	
	//Delete a component
	void deleteComponent(unsigned int id);
};

