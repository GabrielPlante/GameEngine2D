#include "Entity.h"

#include "TransformComponent.h"
#include "Storage.h"

namespace ge {
	IDGenerator<unsigned int> Entity::idGenerator = IDGenerator<unsigned int>{};

	Entity Entity::Create() {
		//Create the entity
		Entity entity;

		//Make a copy of the entity because the original one will be moved into the storage
		Entity entityHandle{ entity };

		//Add the entity to the storage
		Storage<Entity>::addComponent(std::move(entity), entityHandle);

		//Add it's transform component
		entityHandle.addComponent(TransformComponent{});

		return entityHandle;
	}
}
