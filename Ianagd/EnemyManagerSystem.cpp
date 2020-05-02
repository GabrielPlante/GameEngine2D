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
		if (F_FACTORY->gameComponent.startNewWave == goForNextWave) {
			F_FACTORY->gameComponent.startNewWave = waveInProgress;
			waveNbr++;
			wave = std::unique_ptr<Wave>{ new Wave{gv::wavesValues[waveNbr - 1].nbrOfEnemy, gv::wavesValues[waveNbr - 1].enemyHealth,
				gv::wavesValues[waveNbr - 1].enemySpeed, spawnTile, destinationTile, gv::wavesValues[waveNbr - 1].color} };
		}
		//If we are in a wave
		else if (F_FACTORY->gameComponent.startNewWave == waveInProgress) {
			ge::Vector2<int> waveStat{ wave->update() };
			//If any enemy cross the line
			if (waveStat.y > gv::nbrOfEnemyForLoss) {
				hasGameEnded = true;
				F_FACTORY->gameComponent.startNewWave = playerLost;
			}
			//If the wave ended
			else if (wave->checkWaveEnded()) {
				wave.reset();
				F_FACTORY->gameComponent.startNewWave = interWave;
				if (waveNbr == gv::wavesValues.size()) {
					hasGameEnded = true;
					F_FACTORY->gameComponent.startNewWave = playerWin;
				}
				else {
					F_FACTORY->positionFactory.getComponent(F_FACTORY->uiFactory.getComponent(F_FACTORY->gameComponent.starterUiId)->positionComponentId)
						->setPosition(ge::Vector2<>{0, 0});
				}
			}
			F_FACTORY->gameComponent.playerGold += waveStat.x * gv::wavesValues[waveNbr - 1].goldPerEnemy;
		}
		if (hasGameEnded) {
			wave.reset();
			GameCore::getInstance()->endGame();
		}

	}
}
