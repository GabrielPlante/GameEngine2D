#pragma once
#include <vector>
#include <unordered_map>

namespace ge {
	/*
	 * Storage is the template class that hold every component of a component type.
	 * The user of this class need to provide an id for each component.
	 * You should use this class only in a system. To manage component use Entity.
	 * The class is optimised to be iterated.
	*/
	template <typename Component>
	class Storage
	{
	private:
		//Where the component are stored
		static std::vector<Component> componentList;
		//The map with id in key and the place of the component in the component list in value (allow to retrieve the component place with the key)
		static std::unordered_map<uint32_t, uint32_t> idToPlace;
		//The vector that allow to retrieve the id from the place
		static std::vector<uint32_t> placeToID;

		friend class Entity;
		//No other choice
		friend struct ComponentHandler;

		//Method to handle component are private to only be accessed by an entity(which is a friend class)

		//Add a component to the list with an id, return the component
		static Component& addComponent(Component&& component, uint32_t id);

		//Get a component by his id
		static Component& get(unsigned long id) { return componentList[idToPlace.find(id)->second]; }

		//Delete a component
		static void deleteComponent(uint32_t id);

	public:
		class StorageIterator {
		private:
			//The intern index
			uint32_t index;

		public:
			//Get the id of this component
			uint32_t id() const { return placeToID[index]; }

			StorageIterator(uint32_t index) : index{ index } {}

			Component* operator->() {
				return &Storage::componentList[index];
			}

			Component& operator*() {
				return Storage::componentList[index];
			}

			StorageIterator& operator++() {
				index++;
				return *this;
			}

			StorageIterator operator++(int) {
				StorageIterator it{ *this };
				StorageIterator::operator++();
				return it;
			}

			bool operator==(const StorageIterator& other) const {
				return index == other.index;
			}

			bool operator!=(const StorageIterator& other) const {
				return !(*this == other);
			}
		};

		using iterator = StorageIterator;

		//Get the iterator to the first element of the list
		static typename iterator begin() { return iterator{ 0 }; }

		//Get the iterator to the end of the list (the element past the last element)
		static typename iterator end() { return iterator{ static_cast<uint32_t>(componentList.size()) }; }

		static void clear();
	};

	//Initialise the static variables
	template <typename T>
	std::vector<T> Storage<T>::componentList;
	template <typename T>
	std::unordered_map<uint32_t, uint32_t> Storage<T>::idToPlace;
	template <typename T>
	std::vector<uint32_t> Storage<T>::placeToID;


	//Function definition are here because of template restriction

	template <typename Component>
	Component& Storage<Component>::addComponent(Component&& component, uint32_t id) {
		//Keep the vector sorted (start at the end because the element is more likely to be at the end)
		auto i{ placeToID.size() };

		while (i > 0 && placeToID[i - 1] > id) {
			i--;
		}

		//Insert the element in the map, and at the same time check if there isn't already a component with the same id
		if (idToPlace.insert(std::make_pair<uint32_t, uint32_t>(std::move(id), static_cast<uint32_t>(i))).second == false) {
			return componentList[i];
		}

		//Add the component on the top of the vector
		componentList.insert(componentList.begin() + i, component);

		//Push the id in the place to id vector
		placeToID.insert(placeToID.begin() + i, id);

		return componentList[i];
	}

	template <typename Component>
	void Storage<Component>::deleteComponent(uint32_t id) {
		//Get the place of the component to delete
		uint32_t componentPlace{ idToPlace.find(id)->second };

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
