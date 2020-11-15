#include "Entity.h"

namespace ge {
	IDGenerator<unsigned int> Entity::idGenerator = IDGenerator<unsigned int>{};

	Entity Entity::Create(TransformComponent&& transform) {
		//Create the entity
		Entity entity;

		//Add the component handler
		ComponentHandler componentHandler{ entity };
		Storage<ComponentHandler>::addComponent(std::move(componentHandler), entity);

		//Add it's transform component
		entity.addComponent(std::move(transform));

		return entity;
	}
}
