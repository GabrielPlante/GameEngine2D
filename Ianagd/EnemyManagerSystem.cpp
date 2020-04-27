#include "EnemyManagerSystem.h"

#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "PathFinder.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	EnemyManagerSystem::EnemyManagerSystem(ge::Vector2<int> spawnTile, ge::Vector2<int> destinationTile)
		: spawnTile{ spawnTile }, destinationTile{ destinationTile }, timeSinceLastWave{ ge::Engine::getInstance()->getTimeSinceStart() }
	{
	}

	void EnemyManagerSystem::update() {
		if (hasGameEnded)
			return;
		//If we aren't in a wave
		if (timeSinceLastWave != 0) {
			//If it is time to begin a new wave
			if (ge::Engine::getInstance()->getTimeSinceStart() - timeSinceLastWave > gv::timeBetweenWaves) {
				waveNbr++;
				timeSinceLastWave = 0;
				wave = std::unique_ptr<Wave>{ new Wave{gv::wavesValues[waveNbr - 1].nbrOfEnemy, gv::wavesValues[waveNbr - 1].enemyHealth,
					gv::wavesValues[waveNbr - 1].enemySpeed, spawnTile, destinationTile, gv::wavesValues[waveNbr - 1].color} };
			}
		}
		//If we are in a wave
		else{
			ge::Vector2<int> waveStat{ wave->update() };
			F_FACTORY->gameComponent.playerGold += waveStat.x * gv::wavesValues[waveNbr - 1].goldPerEnemy;
			//If the wave ended
			if (wave->checkWaveEnded()) {
				timeSinceLastWave = ge::Engine::getInstance()->getTimeSinceStart();
				wave.reset();
				if (waveNbr == gv::wavesValues.size()) {
					hasGameEnded = true;
				}
			}
		}
	}
}
