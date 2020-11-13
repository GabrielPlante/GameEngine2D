#pragma once

#include "EntityHandle.h"
#include "IDGenerator.h"
#include "Storage.h"

namespace ge {	
	//An entity
	class Entity
	{
	private:
		static IDGenerator<unsigned int> idGenerator;

		//The id of the entity
		unsigned int id;

		//This is because the storage need to create default composant in case an added component got an ID too big
		//However, this will never happen in the entity class since it dictate the ID generated
		friend class Storage<Entity>;
		//Constructor
		Entity() : id{ idGenerator.getNewID() } {}
	public:
		//Create an entity, add it to the entity storage and return the id of the entity
		static EntityHandle Create();

		//Get the id of this entity
		unsigned int getID() const { return id; }

		//Add a component to this entity
		template <typename Component>
		void addComponent(Component&& component) const { Storage<Component>::addComponent(std::move(component), id); }

		//Get a component from this entity
		template <typename Component>
		Component* getComponent() const { return Storage<Component>::getComponent(id); }

		//Delete a component
		template <typename Component>
		void deleteComponent() const { Storage<Component>::deleteComponent(id); }
	};
}
