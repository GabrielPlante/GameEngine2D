#pragma once
#include <vector>
#include <unordered_set>

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
		static std::unordered_set<unsigned int> unusedComponentSet;

		friend class Entity;

		//Add a component to the list with an id, return true if the id was not taken
		static bool addComponent(Component&& component, unsigned int id);

		//Get a component by his id
		static Component& get(unsigned long id) { return componentList[id]; }

		//Delete a component
		static void deleteComponent(unsigned int id);

	public:
		class StorageIterator {
		private:
			//The intern index of the unused component list
			std::unordered_set<unsigned int>::iterator unusedComponentSetIT{ unusedComponentSet.begin() };
		public:
			//The intern index
			unsigned int index;

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
				//If this component is not used
				while (unusedComponentSetIT != Storage::unusedComponentSet.end() && 
					*unusedComponentSetIT == index) {
					unusedComponentSetIT++;

					index++;
				}
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

	template <typename T>
	std::vector<T> Storage<T>::componentList;
	template <typename T>
	std::unordered_set<unsigned int> Storage<T>::unusedComponentSet;


	//Function definition are here because of template restriction

	template <typename Component>
	bool Storage<Component>::addComponent(Component&& component, unsigned int id) {
		//First case : the vector is smaller than the id

		while (componentList.size() < id)
			componentList.push_back(Component{});

		//If the vector is juste one smaller than the id, then this component should be the next one
		if (componentList.size() == id) {
			componentList.push_back(component);
			return true;
		}

		//Second case : the id already exist
		//Maybe it is deleted
		if (unusedComponentSet.find(id) != unusedComponentSet.end()) {
			//If it is the case, mark it as not deleted and replace the deleted one
			unusedComponentSet.erase(id);
			componentList[id] = component;
			return true;
		}
		//Else, it is already in use, return false
		return false;
	}

	template <typename Component>
	void Storage<Component>::deleteComponent(unsigned int id) {
		//Mark the id as being unused
		unusedComponentSet.insert(id);
	}

	template <typename Component>
	void Storage<Component>::clear() {
		//Clear the vector containing the object
		componentList.clear();

		//Clear the map
		unusedComponentSet.clear();
	}

}
