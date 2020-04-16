#pragma once
#include "../GameEngine2D/Factory.h"

#include "GameEntity.h"
#include "PositionComponent.h"
#include "RendererComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "TileComponent.h"

#include "Map.h"

namespace ian {
	/// <summary>
	/// This class contain every factory in the game
	/// <para>The factory are made public to avoid 5 methods per factory (add, delete, get, getBegIterator and getEndIterator)</para>
	/// </summary>
	class FactoryFactory {
	private:
	public:
		//Create an game entity with a list of component
		unsigned int createEntity(const std::vector<int>& componentList);

		//Get a component from an entity
		unsigned int getEntityCompId(unsigned int entityId, int type) { return entityFactory.getComponent(entityId)->getComponentId(type); }

		ge::Factory<GameEntity> entityFactory;

		ge::Factory<PositionComponent> positionFactory;

		ge::Factory<RendererComponent> rendererFactory;

		ge::Factory<MovementComponent> movementFactory;

		ge::Factory<CollisionComponent> collisionFactory;

		Map map;
	};
}
