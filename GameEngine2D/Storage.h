#pragma once
#include <vector>
#include <unordered_map>

namespace ge {
	/*
	 * Storage is the template class that hold every component of a component type
	 * The user of this class need to provide an id for each component
	*/
	template <typename Component>
	class Storage
	{
	private:
		static std::vector<Component> componentList;
		static std::unordered_map<unsigned int, unsigned int> iDtoPlace;

		friend class Entity;

		//Add a component to the list with an id, return true if the id was not taken
		static bool addComponent(Component&& component, unsigned int id);

	public:
		//Get a component by his id
		static Component* getComponent(unsigned long id) { return &componentList[iDtoPlace.find(id)->second]; }

		//Get the iterator to the first element of the list
		static typename std::vector<Component>::iterator begin() { return componentList.begin(); }

		//Get the iterator to the end of the list (the element past the last element)
		static typename std::vector<Component>::iterator end() { return componentList.end(); }

		//Delete a component
		static void deleteComponent(unsigned int id);

		//Clear the factory
		static void clear();
	};

	template <typename T>
	std::vector<T> Storage<T>::componentList{};
	template <typename T>
	std::unordered_map<unsigned int, unsigned int> Storage<T>::iDtoPlace{};


	//Function definition are here because of template restriction

	template <typename Component>
	bool Storage<Component>::addComponent(Component&& component, unsigned int id) {
		//If the id already exist, return false
		if (iDtoPlace.find(id) != iDtoPlace.end()) {
			return false;
		}
		else {
			//Push the component in the list
			componentList.push_back(component);

			//Insert ID in the map
			unsigned int componentListSize{ static_cast<unsigned int>(componentList.size() - 1) };
			iDtoPlace.insert(std::make_pair(id, componentListSize));

			return true;
		}
	}

	template <typename Component>
	void Storage<Component>::deleteComponent(unsigned int id) {
		//Get the place of the component to delete
		unsigned int componentPlace{ iDtoPlace.find(id)->second };

		//Delete the component
		componentList.erase(componentList.begin() + componentPlace);

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
	void Storage<Component>::clear() {
		//Clear the vector containing the object
		componentList.clear();

		//Clear the map
		iDtoPlace.clear();
	}

}
