#include "EnemyManagerSystem.h"

#include "../GameEngine2D/Rectangle.h"
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
		if (pathStack.empty()) {
			PathFinder pathFinder{ spawnTile, destinationTile };
			pathStack = pathFinder.findPath();
		}
		if (waveNbr == 0) {
			waveNbr++;
			//Create an entity
			unsigned int entityId{ F_FACTORY->createEntity({ tileMovementCompId, healthCompId, positionCompId, rendererCompId }) };
			//Draw his texture
			ge::Drawer drawer;
			SDL_Renderer* renderer{ drawer.startDrawing(ge::Vector2<int>{50, 50}, ge::Color{255, 0, 0, 255}) };
			SDL_Rect rect{ ge::Rectangle{0, 0, 50, 50}.toSDL_Rect() };
			SDL_RenderFillRect(renderer, &rect);//Draw a simple rectangle
			SDL_Texture* texture = drawer.finishDrawing();
		
			F_FACTORY->entityFactory.getComponent(entityId)
				->managePosition(F_FACTORY->map.relativeToAbsolute(spawnTile))
				->manageTileMovement(pathStack, 0.2f, true)
				->manageHealth(100)
				->manageRenderer(texture, { 50, 50 });
		}
	}
}
