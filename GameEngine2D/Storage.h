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
		//Where the component are stored
		static std::vector<Component> componentList;
		//The map with id in key and the place of the component in the component list in value (allow to retrieve the component place with the key)
		static std::unordered_map<unsigned int, unsigned int> idToPlace;
		//The vector that allow to retrieve the id from the place
		static std::vector<unsigned int> placeToID;

		friend class Entity;

		//Method to handle component are private to only be accessed by an entity(wich is a friend class)

		//Add a component to the list with an id, return the component
		static Component& addComponent(Component&& component, unsigned int id);

		//Get a component by his id
		static Component& get(unsigned long id) { return componentList[idToPlace.find(id)->second]; }

		//Delete a component
		static void deleteComponent(unsigned int id);

	public:
		class StorageIterator {
		private:
			//The intern index
			unsigned int index;

		public:
			//Get the id of this component
			unsigned int id() const { return placeToID[index]; }

			//Constructor
			StorageIterator(unsigned int index) : index{ index } {}

			//Operator ->
			Component* operator->() {
				return &Storage::componentList[index];
			}

			//Operator *
			Component& operator*() {
				return Storage::componentList[index];
			}

			//Prefix incrementor
			StorageIterator& operator++() {
				index++;
				return *this;
			}

			//Post fix operator
			StorageIterator operator++(int) {
				StorageIterator it{ *this };
				StorageIterator::operator++();
				return it;
			}

			//Operator ==
			bool operator==(const StorageIterator& other) const {
				return index == other.index;
			}

			//Operator !=
			bool operator!=(const StorageIterator& other) const {
				return !(*this == other);
			}
		};

		using iterator = StorageIterator;

		//Get the iterator to the first element of the list
		static typename iterator begin() { return iterator{ 0 }; }

		//Get the iterator to the end of the list (the element past the last element)
		static typename iterator end() { return iterator{ static_cast<unsigned int>(componentList.size()) }; }

		//Clear the factory
		static void clear();
	};

	//Initialise the statis variable
	template <typename T>
	std::vector<T> Storage<T>::componentList;
	template <typename T>
	std::unordered_map<unsigned int, unsigned int> Storage<T>::idToPlace;
	template <typename T>
	std::vector<unsigned int> Storage<T>::placeToID;


	//Function definition are here because of template restriction

	template <typename Component>
	Component& Storage<Component>::addComponent(Component&& component, unsigned int id) {
		//Keep the vector sorted (start at the end because the element is more likely to be at the end)
		auto i{ placeToID.size() };

		while (i > 0 && placeToID[i - 1] > id) {
			i--;
		}

		//Insert the element in the map, and at the same time check if there isn't already a component with the same id
		if (idToPlace.insert(std::make_pair<unsigned int, unsigned int>(std::move(id), static_cast<unsigned int>(i))).second == false) {
			return componentList[i];
		}

		//Add the component on the top of the vector
		componentList.insert(componentList.begin() + i, component);

		//Push the id in the place to id vector
		placeToID.insert(placeToID.begin() + i, id);

		return componentList[i];
	}

	template <typename Component>
	void Storage<Component>::deleteComponent(unsigned int id) {
		//Get the place of the component to delete
		unsigned int componentPlace{ idToPlace.find(id)->second };

		//Delete the component
		componentList.erase(componentList.begin() + componentPlace);

		placeToID.erase(placeToID.begin() + componentPlace);

		//Delete the ID in the table
		idToPlace.erase(id);

		//Decrement the place of all other component
		auto it = idToPlace.begin();
		while (it != idToPlace.end()) {
			if (it->second > componentPlace) {
				it->second--;
			}
			it++;
		}
	}

	template <typename Component>
	void Storage<Component>::clear() {
		//Clear the 3 containers
		componentList.clear();

		placeToID.clear();

		idToPlace.clear();
	}

}
