#pragma once
#include "../GameEngine2D/Factory.h"
#include "../GameEngine2D/Entity.h"

#include "PhysicComponent.h"
#include "PositionComponent.h"

namespace ian {
	/// <summary>
	/// This class contain every factory in the game
	/// <para>The factory are made public to avoid 5 methods per factory (add, delete, get, getBegIterator and getEndIterator)</para>
	/// </summary>
	class FactoryFactory {
	private:
	public:
		//The entity factory
		ge::Factory<ge::Entity> entityFactory;

		//The position factory, here lie all the position in the game
		ge::Factory<PositionComponent> positionFactory;

		//The physic factory
		ge::Factory<PhysicComponent> physicFactory;

	};
}
