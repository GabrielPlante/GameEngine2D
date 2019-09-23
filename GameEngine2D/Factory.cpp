#include "Factory.h"

template <typename Component>
unsigned int Factory<Component>::addComponent(Component component) {
	//Push the component in the list
	componentList.push_back(component);

	//Get the ID for this component
	unsigned int id{ iDGenerator.getNewID() };

	//Insert ID in the map
	unsigned int componentListSize{ static_cast<unsigned int>(componentList.size() - 1) };
	iDtoPlace.insert(std::make_pair(id, componentListSize));

	return id;
}

template <typename Component>
void Factory<Component>::deleteComponent(unsigned int id) {
	//Get the place of the component to delete
	unsigned int componentPlace{ iDtoPlace.find(id)->second };

	//Delete the component
	componentList.erase(componentList.begin() + componentPlace);

	//Delete the ID in the table
	iDtoPlace.erase(id);

	//Decrement the place of all other component
	auto it = iDtoPlace.begin();
	while (it != iDtoPlace.end()) {
		if (it->second > componentPlace) {
			it->second--;
		}
		it++;
	}
}
