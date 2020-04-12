#pragma once
#include "../GameEngine2D/Camera.h"

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

		ge::Camera camera;

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

		//Get a camera pointer
		ge::Camera* getCamera() { return &camera; }

		//Get factory factory pointer
		FactoryFactory* getFactoryFactory() { return &factoryFactory; }

		//Run the game
		void run();
	};
}
