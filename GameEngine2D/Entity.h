#pragma once

#include "IDGenerator.h"
#include "Storage.h"

namespace ge {	
	/* Every component in the game is created and belong to an entity
	* The class entity provide tool to manage component and access component
	* This class can be used as a handle
	*/
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
		//Copy constructor and constructor from an unsigned are ok because the id stay the same
		Entity(const Entity& entity) : id{ entity.id } {}
		Entity(unsigned int id) : id{ id } {}

		//Create an entity, add it to the entity storage and return the id of the entity
		static Entity Create();

		//Add a component to this entity
		template <typename Component>
		void addComponent(Component&& component) const { Storage<Component>::addComponent(std::move(component), id); }

		//Get a component from this entity
		template <typename Component>
		Component& getComponent() const { return Storage<Component>::get(id); }

		//Delete a component
		template <typename Component>
		void deleteComponent() const { Storage<Component>::deleteComponent(id); }

		//Operator to convert to unsigned int
		operator unsigned int() const { return id; }
	};
}
