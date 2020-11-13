#pragma once

#include "Storage.h"

namespace ge {
	class Entity;
	class EntityHandle {
	private:
		unsigned int entityID;
	public:
		//Construtor
		EntityHandle(unsigned int entityID) : entityID{ entityID } {}

		//Get the id
		unsigned int get() const { return entityID; }

		//Get the entity pointed by this handle
		Entity& getEntity() const { return Storage<Entity>::get(entityID); }

		//Add a component to this entity
		template <typename Component>
		void addComponent(Component&& component) const { Storage<Entity>::get(entityID).addComponent(std::move(component)); }

		//Get a component from this entity
		template <typename Component>
		Component* getComponent() const { return Storage<Component>::getComponent(entityID); }

		//Delete a component
		template <typename Component>
		void deleteComponent() const { Storage<Component>::deleteComponent(entityID); }

		//Operator for implicit conversion to unsigned int
		operator unsigned int() const { return entityID; }
	};
}
