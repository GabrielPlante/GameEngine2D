#include "TowerManager.h"

#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

#include <iostream>

namespace ian {
	bool TowerManager::buildTower(ge::Vector2<> position, int type) {
		//If the player doesn't have enough money to buy it
		if (F_FACTORY->gameComponent.playerGold < gv::towersValues[type].cost)
			return false;
		//If the tile is buildable
		if (F_FACTORY->map.tileExist(F_FACTORY->map.absoluteToRelative(position))
			&& F_FACTORY->map.getTile(F_FACTORY->map.absoluteToRelative(position)).isBuildable) {
			//Check if no other tower are on the tile
			for (auto it = towersId.begin(); it != towersId.end(); it++) {
				unsigned int damageCompId{ F_FACTORY->getEntityCompId(*it, damageDealerCompId) };
				if (F_FACTORY->map.absoluteToRelative(F_FACTORY->positionFactory.getComponent(F_FACTORY->damageDealerFactory.getComponent(damageCompId)->positionComponentId)
					->getPosition()) == F_FACTORY->map.absoluteToRelative(position)) {

					return false;
				}
			}

			//Draw the tower texture
			ge::Drawer drawer;
			SDL_Renderer* renderer{ drawer.startDrawing({gv::tileSize, gv::tileSize}, gv::towersValues[type].color) };
			SDL_Rect rect{ ge::Rectangle{0, 0, gv::tileSize, gv::tileSize}.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &rect);
			ge::TextureWrapper texture{ drawer.finishDrawing() };
			
			//Build the tower
			unsigned int towerId{ F_FACTORY->createEntity({positionCompId, damageDealerCompId, rendererCompId}) };
			//positionComponent.setPosition();
			F_FACTORY->entityFactory.getComponent(towerId)
				->managePosition(F_FACTORY->map.relativeToAbsolute(F_FACTORY->map.absoluteToRelative(position)))
				->manageDamageDealer(gv::towersValues[type].damage, gv::towersValues[type].range, gv::towersValues[type].reloadingTime)
				->manageRenderer(texture);

			F_FACTORY->gameComponent.playerGold -= gv::towersValues[type].cost;

			towersId.push_back(towerId);

			return true;
		}
		return false;
	}
}
