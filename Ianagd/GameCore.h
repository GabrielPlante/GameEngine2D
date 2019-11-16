#pragma once

#include "FactoryFactory.h"

namespace ian {
	/// <summary>
	/// The core of the game, here the engine is managed
	/// <para>It is a singleton for global access</para>
	/// </summary>
	class GameCore
	{
	private:
		FactoryFactory factoryFactory;

		static GameCore* instance;

		//Default constructor, private because it is a singleton
		GameCore();

		//Destructor
		~GameCore();

	public:
		//Init the game core
		static void init();

		//Get the game core instance, return nullptr if the gamecore is not initialized
		static GameCore* getInstance() { return instance; }

		//Quit the game core
		static void quit();

		//Run the game
		void run();
	};
}
