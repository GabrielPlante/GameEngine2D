#include "DamageDealerSystem.h"

#include "../GameEngine2D/Engine.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {
	void DamageDealerSystem::update() {
		//For every damage dealer component
		for (auto itd = F_FACTORY->damageDealerFactory.getBeginningIterator(); itd != F_FACTORY->damageDealerFactory.getEndIterator(); itd++) {
			//If this damage dealer can shoot again
			if (ge::Engine::getInstance()->getTimeSinceStart() - itd->lastShotTime > static_cast<long long>(itd->reloadingTime)) {
				//For every health component
				for (auto ith = F_FACTORY->healthFactory.getBeginningIterator(); ith != F_FACTORY->healthFactory.getEndIterator(); ith++) {
					//If the health is in range of this damage dealer
					if (F_FACTORY->positionFactory.getComponent(itd->positionComponentId)->position.distanceSquared(
						F_FACTORY->positionFactory.getComponent(ith->positionComponentId)->position) < pow(itd->range, 2)) {
						//Shot it
						ith->health -= itd->damage;
						itd->lastShotTime = ge::Engine::getInstance()->getTimeSinceStart();
						//Escape this for loop to pass to the next damage dealer
						break;
					}
				}
			}
		}
	}
}
