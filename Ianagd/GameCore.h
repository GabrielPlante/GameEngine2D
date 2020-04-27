#pragma once
#include <memory>

#include "../GameEngine2D/Vector2.h"


#define F_FACTORY ian::GameCore::getInstance()->getFactoryFactory()

namespace ge {
	class Camera;
}
namespace ian {
	class MovementSystem;
	class FactoryFactory;
	/// <summary>
	/// The core of the game, here the engine is managed
	/// <para>It is a singleton for global access</para>
	/// </summary>
	class GameCore
	{
	private:
		FactoryFactory* factoryFactory;

		ge::Camera* camera;

		//The id of the player
		unsigned int playerId;

		static GameCore* instance;

		//Default constructor, private because it is a singleton
		GameCore();

		//Destructor
		~GameCore();

		//Setup the map, the player...
		void setupGame();

	public:
		//Init the game core
		static void init();

		//Get the game core instance, return nullptr if the gamecore is not initialized
		static GameCore* getInstance() { return instance; }

		//Quit the game core
		static void quit();

		//Get a camera pointer
		ge::Camera* getCamera() { return camera; }

		//Get factory factory pointer
		FactoryFactory* getFactoryFactory() { return factoryFactory; }

		//Get the player id
		unsigned int getPlayerId() const { return playerId; }

		//Run the game
		void run();
	};
}
