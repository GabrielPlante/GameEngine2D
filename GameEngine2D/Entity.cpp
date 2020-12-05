#include "Entity.h"

namespace ge {
	IDGenerator<uint32_t> Entity::idGenerator = IDGenerator<uint32_t>{};

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
