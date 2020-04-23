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
				switch (waveNbr)
				{
				case 1:
					wave = std::unique_ptr<Wave>{ new Wave{gv::wave1.nbrOfEnemy, gv::wave1.enemyHealth, gv::wave1.enemySpeed,
						spawnTile, destinationTile, {100, 0, 0}} };
					break;
				case 2:
					wave = std::unique_ptr<Wave>{ new Wave{gv::wave2.nbrOfEnemy, gv::wave2.enemyHealth, gv::wave3.enemySpeed,
						spawnTile, destinationTile, {128, 80, 80}} };
					break;
				case 3:
					wave = std::unique_ptr<Wave>{ new Wave{gv::wave3.nbrOfEnemy, gv::wave3.enemyHealth, gv::wave3.enemySpeed,
						spawnTile, destinationTile, {255, 0, 0}} };
					break;
				}
			}
		}
		//If we are in a wave
		else{
			wave->update();
			//If the wave ended
			if (wave->checkWaveEnded()) {
				timeSinceLastWave = ge::Engine::getInstance()->getTimeSinceStart();
				wave.reset();
				if (waveNbr == gv::nbrOfWave)
					hasGameEnded = true;
			}
		}
	}
}
