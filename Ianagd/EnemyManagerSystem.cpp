#include "EnemyManagerSystem.h"

#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "PathFinder.h"
#include "GameCore.h"

namespace ian {
	EnemyManagerSystem::EnemyManagerSystem(ge::Vector2<int> spawnTile, ge::Vector2<int> destinationTile)
		: spawnTile{ spawnTile }, destinationTile{ destinationTile }
	{
	}

	void EnemyManagerSystem::update() {
		if (waveNbr == 0) {
			waveNbr++;
			wave = std::unique_ptr<Wave>{ new Wave{5, 100, 1, spawnTile, destinationTile, {100, 0, 0}} };
		}
		else if (waveNbr == 1) {
			wave->update();
			if (wave->checkWaveEnded()) {
				wave.reset();
				waveNbr++;
			}
		}
	}
}
