#include "Wave.h"

#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "PathFinder.h"
#include "GameCore.h"

namespace ian {
	void Wave::spawnEnemy() {
		unsigned int entityId{ F_FACTORY->createEntity({positionCompId, rendererCompId, tileMovementCompId, healthCompId}) };
		F_FACTORY->entityFactory.getComponent(entityId)
			->managePosition(F_FACTORY->map.relativeToAbsolute(startTile))
			->manageRenderer(enemyTexture, { gv::tileSize, gv::tileSize })
			->manageTileMovement(pathStack, enemySpeed, true)
			->manageHealth(enemyHealth);
		entityIdList.push_back(entityId);
	}

	Wave::Wave(int nbrOfEnemy, int enemyHealth, float enemySpeed, ge::Vector2<int> startTile, ge::Vector2<int> destinationTile, ge::Color enemyColor)
		: lastSpawn{ ge::Engine::getInstance()->getTimeSinceStart() }, nbrOfEnemy{ nbrOfEnemy }, enemyHealth{ enemyHealth }, enemySpeed{ enemySpeed },
		startTile{ startTile }, destinationTile{ destinationTile }
	{
		//Make the path
		PathFinder pathFinder{ startTile, destinationTile };
		pathStack = pathFinder.findPath();

		//Make the texture (one for every entity)
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({gv::tileSize, gv::tileSize}, enemyColor) };
		SDL_Rect rect{ ge::Rectangle{0, 0, gv::tileSize, gv::tileSize}.toSDL_Rect() };
		SDL_RenderFillRect(renderer, &rect);
		enemyTexture = drawer.finishDrawing();

		//Spawn one entity
		spawnEnemy();
		this->nbrOfEnemy--;
	}

	ge::Vector2<int> Wave::update() {
		//If there is still enemy that need to spawn and the time is up for it to spawn
		if (nbrOfEnemy > 0 && ge::Engine::getInstance()->getTimeSinceStart() - lastSpawn > gv::timeBetweenSpawn) {
			lastSpawn = ge::Engine::getInstance()->getTimeSinceStart();
			spawnEnemy();
			nbrOfEnemy--;
		}

		ge::Vector2<int> updatedEntities;
		updatedEntities.x = checkDead();
		updatedEntities.y = checkFinished();
		return updatedEntities;
	}

	int Wave::checkDead() {
		int nbrOfDead{ 0 };
		auto it = entityIdList.begin();
		while (it != entityIdList.end()) {
			//If it is dead
			if (F_FACTORY->healthFactory.getComponent(F_FACTORY->getEntityCompId(*it, healthCompId))->health <= 0) {
				//Delete the entity from the entity factory
				F_FACTORY->deleteEntity(*it);
				//Delete the entity from the list of active entity in this wave
				it = entityIdList.erase(it);
				//Take in account his death
				nbrOfDead++;
			}
			else
				it++;
		}
		return nbrOfDead;
	}

	int Wave::checkFinished() {
		int nbrOfFinished{ 0 };
		auto it = entityIdList.begin();
		while (it != entityIdList.end()) {
			//If it finished
			if (F_FACTORY->map.absoluteToRelative(F_FACTORY->positionFactory.getComponent(F_FACTORY->getEntityCompId(*it, positionCompId))->position) == destinationTile) {
				//Delete the entity from the entity factory
				F_FACTORY->deleteEntity(*it);
				//Delete the entity from the list of active entity in this wave
				it = entityIdList.erase(it);
				//Take in account his death
				nbrOfFinished++;
			}
			else
				it++;
		}
		return nbrOfFinished;
	}
}
