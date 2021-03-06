#pragma once

#include "TransformComponent.h"
#include "ComponentHandler.h"
#include "IDGenerator.h"
#include "Storage.h"

namespace ge {	
	/* Every component in the game is created and belong to an entity
	* The class entity provide tool to manage component and access component
	*/
	class Entity
	{
	private:
		static IDGenerator<uint32_t> idGenerator;

		//The id of the entity
		uint32_t id;

		//Constructor
		Entity() : id{ idGenerator.getNewID() } {}

	public:
		//Copy constructor and constructor from an unsigned are ok because the id stay the same
		Entity(const Entity& entity) : id{ entity.id } {}
		Entity(uint32_t id) : id{ id } {}

		//Create an entity, add it to the entity storage and return the id of the entity
		static Entity Create(TransformComponent&& transform = TransformComponent{});

		//Add a component to this entity
		template <typename Component>
		Component& addComponent(Component&& component = Component{}) const { Storage<ComponentHandler>::get(id).addComponent<Component>();
			return Storage<Component>::addComponent(std::move(component), id); }

		//Get a component from this entity
		template <typename Component>
		Component& getComponent() const { return Storage<Component>::get(id); }

		//Check if this entity have a certain component
		template <typename Component>
		bool haveComponent() const { return Storage<Component>::exist(id); }

		//Delete a component
		template <typename Component>
		void deleteComponent() const { Storage<ComponentHandler>::get(id).deleteComponent<Component>(); }

		//Delete the entity and all it's component
		void deleteEntity() { Storage<ComponentHandler>::get(id).clear(); Storage<ComponentHandler>::deleteComponent(id); }

		//Operator to convert to uint32_t
		operator uint32_t() const { return id; }
	};
}
