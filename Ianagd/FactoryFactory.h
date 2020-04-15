#pragma once
#include "../GameEngine2D/Factory.h"

#include "GameEntity.h"
#include "RendererComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

namespace ian {
	/// <summary>
	/// This class contain every factory in the game
	/// <para>The factory are made public to avoid 5 methods per factory (add, delete, get, getBegIterator and getEndIterator)</para>
	/// </summary>
	class FactoryFactory {
	private:
	public:
		ge::Factory<GameEntity> entityFactory;

		ge::Factory<RendererComponent> rendererComponentFactory;

		ge::Factory<MovementComponent> movementComponentFactory;

		ge::Factory<CollisionComponent> collisionComponentFactory;
	};
}
