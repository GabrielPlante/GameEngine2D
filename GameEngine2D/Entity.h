#pragma once

#include "IDGenerator.h"
#include "Storage.h"

namespace ge {	
	//An entity
	class Entity
	{
	private:
		static IDGenerator<unsigned int> idGenerator;

		//The id of the entity
		const unsigned int id;

		//Constructor
		Entity() : id{ idGenerator.getNewID() } {}
	public:
		//Create an entity, add it to the entity storage and return the id of the entity
		static unsigned int Create();

		//Static method to ease the adding a component
		template <typename Component>
		static void addComponent(Component&& component, unsigned int entityID) { Storage<Component>::addComponent(std::move(component), entityID); }

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
