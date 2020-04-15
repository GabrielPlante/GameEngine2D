#pragma once
#include <vector>

#include "Component.h"

namespace ge {	
	/// <summary>
	/// An entity hold an id and a list of component. The components are located in a factory
	/// </summary>
	class Entity
	{
	private:
		//Count what the next entity will have as an id
		static unsigned long idCount;

		//Each entity have a unique id
		const unsigned long id;
	public:
		//Default constructor
		Entity();
	};

}
