#pragma once
#include <vector>

#include "Storage.h"

namespace ge {
	struct ComponentHandler {
	private:
		unsigned int entityID;

		//The vector that store the deleter of each component of an entity
		std::vector<void(*)(unsigned int)> componentDeleter{};

	public:
		//Default constructor
		ComponentHandler(unsigned int entityID) : entityID{ entityID } {}

		//Add a component to this handle
		template<typename Component>
		void addComponent() { componentDeleter.push_back(Storage<Component>::deleteComponent); }

		//Delete a component
		template<typename Component>
		void deleteComponent();

		//Destructor, delete every component
		void clear() {
			//Delete every deleter function
			for (auto it = componentDeleter.begin(); it != componentDeleter.end(); it++)
				(*it)(entityID);
		}
	};


	template<typename Component>
	void ComponentHandler::deleteComponent() {
		//Delete the component
		Storage<Component>::deleteComponent(entityID);
		//Delete the deleter function
		for (size_t i = 0; i != componentDeleter.size(); i++) {
			void(*deleteFunction)(unsigned int);
			deleteFunction = Storage<Component>::deleteComponent;
			if (deleteFunction == componentDeleter[i]) {
				componentDeleter.erase(componentDeleter.begin() + i);
				break;
			}
		}
	}
}
