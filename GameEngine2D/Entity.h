#pragma once

#include "TransformComponent.h"
#include "IDGenerator.h"
#include "Storage.h"

namespace ge {	
	/* Every component in the game is created and belong to an entity
	* The class entity provide tool to manage component and access component
	*/
	class Entity
	{
	private:
		static IDGenerator<unsigned int> idGenerator;

		//The id of the entity
		unsigned int id;

		//Constructor
		Entity() : id{ idGenerator.getNewID() } {}

	public:
		//Copy constructor and constructor from an unsigned are ok because the id stay the same
		Entity(const Entity& entity) : id{ entity.id } {}
		Entity(unsigned int id) : id{ id } {}

		//Create an entity, add it to the entity storage and return the id of the entity
		static Entity Create(TransformComponent&& transform = TransformComponent{});

		//Add a component to this entity
		template <typename Component>
		Component& addComponent(Component&& component = Component{}) const { return Storage<Component>::addComponent(std::move(component), id); }

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
