#pragma once
#include <vector>

#include "ComponentHandle.h"

namespace ge {
	class Entity
	{
	private:
		//Count what the next entity will have as an id
		static unsigned long idCount;

		//Each entity have a unique id
		const unsigned long id;

		//The list of component handle associated with this entity
		std::vector<ComponentHandle> componentHandleList;
	public:
		//Default constructor
		Entity();
		
		//Give the entity another component handle
		void addComponentHandle(ComponentHandle&& componentHandle) { componentHandleList.push_back(componentHandle); }
	};

}
