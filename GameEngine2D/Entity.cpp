#include "Entity.h"

#include "TransformComponent.h"
#include "Storage.h"

namespace ge {
	IDGenerator<unsigned int> Entity::idGenerator = IDGenerator<unsigned int>{};

	Entity Entity::Create(TransformComponent&& transform) {
		//Create the entity
		Entity entity;

		//Add it's transform component
		entity.addComponent(std::move(transform));

		return entity;
	}
}
