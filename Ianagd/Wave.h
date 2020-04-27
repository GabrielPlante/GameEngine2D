#pragma once
#include <vector>
#include <stack>

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Color.h"

struct SDL_Texture;

namespace ian {

	class Wave
	{
		long long lastSpawn;

		//Kept to check if an entity reached it
		ge::Vector2<int> destinationTile;

		std::vector<unsigned int> entityIdList;

		//Enemy properties
		int nbrOfEnemy;
		int enemyHealth;
		float enemySpeed;
		ge::Vector2<int> startTile;
		std::stack<ge::Vector2<int>> pathStack;
		ge::TextureWrapper enemyTexture;

		//Spawn an enemy
		void spawnEnemy();

		//Return the number of entity with health below 0 and delete them
		int checkDead();

		//Return the number of entity that crossed the finish line and delete them
		int checkFinished();
	public:
		//Constructor
		Wave(int nbrOfEnemy, int enemyHealth, float enemySpeed, ge::Vector2<int> startTile, ge::Vector2<int> destinationTile, ge::Color enemyColor);

		//Update the wave. The first int is the number of dead and the second is the number of finished
		ge::Vector2<int> update();

		//Check if the wave ended (ie: all the enemy are dead)
		bool checkWaveEnded() { return entityIdList.empty() && nbrOfEnemy == 0; }

		//Destructor
		~Wave();
	};
}
