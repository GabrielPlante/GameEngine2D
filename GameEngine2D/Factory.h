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
	int addComponent(Component component) {
		//Push the component in the list
		componentList.push_back(component);

		//Get the ID for this component
		unsigned int id = iDGenerator.getNewID();
		//Insert ID in the map
		iDtoPlace.insert(std::make_pair<unsigned int, unsigned int>(id, componentList.size()));
		return id;
	}

	Component* getComponent(unsigned long id) const {
		return &componentList[iDtoPlace.find(id)->second()];
	}
	
	//TODO add the delete component method
	void deleteComponent(unsigned long id) {

	}

};

