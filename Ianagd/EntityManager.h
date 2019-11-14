#pragma once

#include "../GameEngine2D/Factory.h"
#include "../GameEngine2D/Entity.h"

namespace ian {
	class EntityManager
	{
	private:
		ge::Factory<ge::Entity> entityFactory;
	public:
		//Default constructor
		EntityManager() {}
		
		//add an entity, return the id of the entity in the stock
		unsigned int addEntity(ge::Entity&& entity) { return entityFactory.addComponent(std::move(entity)); }
	};
}

