#pragma once

#include "EntityManager.h"

namespace ian {
	/// <summary>
	/// The core of the game, here the engine is managed
	/// </summary>
	class GameCore
	{
	private:
		EntityManager entityManager;
	public:
		//Default constructor
		GameCore();

		//Run the game
		void run();
	};
}
