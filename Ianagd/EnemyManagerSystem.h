#pragma once
#include <vector>
#include <stack>
#include <memory>

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Vector2.h"

#include "Wave.h"

namespace ian {
	class EnemyManagerSystem
		: public ge::System
	{
	private:
		ge::Vector2<int> spawnTile;
		ge::Vector2<int> destinationTile;

		//The number of the actual wave
		int waveNbr{ 0 };

		std::unique_ptr<Wave> wave;

	public:
		//Constructor
		EnemyManagerSystem(ge::Vector2<int> spawnTile, ge::Vector2<int> destinationTile);

		//The update method, called each frame
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}
