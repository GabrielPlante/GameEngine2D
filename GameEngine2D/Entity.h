#pragma once

#include "ComponentHandle.h"
#include "Subscriber.h"

namespace ge {
	class Entity
		: public Subscriber
	{
	private:
		//Count what the next entity will have as an id
		static unsigned long idCount;

		//Each entity have a unique id
		const unsigned long id;

		//The list of component handle associated with this entity
		std::vector<ComponentHandle> componentHandle;
	public:
		//Default constructor
		Entity();
	};

}
