#include "Entity.h"

namespace ge {
	unsigned long Entity::idCount{ 0 };

	Entity::Entity()
		:id{ idCount }
	{
		idCount++;
	}
}
