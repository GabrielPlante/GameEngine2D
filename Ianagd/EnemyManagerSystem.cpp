#include "EnemyManagerSystem.h"

#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Engine.h"

#include "FactoryFactory.h"
#include "PathFinder.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	EnemyManagerSystem::EnemyManagerSystem(ge::Vector2<int> spawnTile, ge::Vector2<int> destinationTile)
		: spawnTile{ spawnTile }, destinationTile{ destinationTile }
	{
	}

	void EnemyManagerSystem::update() {
		if (hasGameEnded)
			return;
		//If it is time to begin a new wave
		if (F_FACTORY->gameComponent.startNewWave == 1) {
			F_FACTORY->gameComponent.startNewWave = 0;
			waveNbr++;
			wave = std::unique_ptr<Wave>{ new Wave{gv::wavesValues[waveNbr - 1].nbrOfEnemy, gv::wavesValues[waveNbr - 1].enemyHealth,
				gv::wavesValues[waveNbr - 1].enemySpeed, spawnTile, destinationTile, gv::wavesValues[waveNbr - 1].color} };
		}
		//If we are in a wave
		else if (F_FACTORY->gameComponent.startNewWave == 0) {
			ge::Vector2<int> waveStat{ wave->update() };
			if (waveStat.y > 0) {
				hasGameEnded = true;
				F_FACTORY->gameComponent.startNewWave = 2;
			}
			F_FACTORY->gameComponent.playerGold += waveStat.x * gv::wavesValues[waveNbr - 1].goldPerEnemy;
			//If the wave ended
			if (wave->checkWaveEnded()) {
				wave.reset();
				F_FACTORY->gameComponent.startNewWave = -1;
				if (waveNbr == gv::wavesValues.size()) {
					hasGameEnded = true;
					F_FACTORY->gameComponent.startNewWave = 3;
				}
				else {
					F_FACTORY->positionFactory.getComponent(F_FACTORY->uiFactory.getComponent(F_FACTORY->gameComponent.starterUiId)->positionComponentId)
						->setPosition(ge::Vector2<>{0, 0});
				}
			}
		}
		if (hasGameEnded) {
			wave.reset();
			GameCore::getInstance()->endGame();
		}
	}
}
