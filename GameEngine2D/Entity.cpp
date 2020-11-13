#include "Entity.h"

#include "Storage.h"

namespace ge {
	IDGenerator<unsigned int> Entity::idGenerator = IDGenerator<unsigned int>{};

	EntityHandle Entity::Create() {
		//Create the entity
		Entity entity;
		unsigned int entityID{ entity.getID() };

		//Add the entity to the storage
		Storage<Entity>::addComponent(std::move(entity), entityID);

		return entityID;
	}
}
