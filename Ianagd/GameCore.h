#pragma once
#include <memory>

#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"

#define F_FACTORY ian::GameCore::getInstance()->getFactoryFactory()

namespace ian {
	class MovementSystem;
	/// <summary>
	/// The core of the game, here the engine is managed
	/// <para>It is a singleton for global access</para>
	/// </summary>
	class GameCore
	{
	private:
		FactoryFactory factoryFactory;

		ge::Camera camera;

		//All the control system
		std::shared_ptr<MovementSystem> movementSystem;

		//The id of the player
		unsigned int playerId;

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

		//Set a destination for a component
		void setDestination(unsigned int componentId, ge::Vector2<> destination) const;

		//Get the player id
		unsigned int getPlayerId() const { return playerId; }

		//Run the game
		void run();
	};
}
