#pragma once
#include "../GameEngine2D/Factory.h"

#include "RendererComponent.h"
#include "GameEntity.h"

namespace ian {
	/// <summary>
	/// This class contain every factory in the game
	/// <para>The factory are made public to avoid 5 methods per factory (add, delete, get, getBegIterator and getEndIterator)</para>
	/// </summary>
	class FactoryFactory {
	private:
	public:
		//The entity factory
		ge::Factory<GameEntity> entityFactory;

		ge::Factory<RendererComponent> rendererComponentFactory;
	};
}
