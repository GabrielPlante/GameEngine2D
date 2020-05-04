#pragma once
#include <vector>
#include <unordered_map>

#include "IDGenerator.h"


namespace ge {
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
		unsigned int addComponent(Component&& component);

		//Get a component by his id
		Component* getComponent(unsigned long id) { return &componentList[iDtoPlace.find(id)->second]; }

		//Get the iterator to the first element of the list
		typename std::vector<Component>::iterator getBeginningIterator() { return componentList.begin(); }

		//Get the iterator to the end of the list (the element past the last element)
		typename std::vector<Component>::iterator getEndIterator() { return componentList.end(); }

		//Delete a component
		void deleteComponent(unsigned int id);

		//Clear the factory
		void clear();
	};


	//Function definition are here because of template restriction

	template <typename Component>
	unsigned int Factory<Component>::addComponent(Component&& component) {
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

	template <typename Component>
	void Factory<Component>::clear() {
		//Clear the vector containing the object
		componentList.clear();

		//Clear the map
		iDtoPlace.clear();

		//Reset the id generator
		iDGenerator = IDGenerator<>{};

	}

}
