#include "Entity.h"

unsigned long Entity::idCount{ 0 };

Entity::Entity()
	:id{ idCount }
{
	idCount++;
}
