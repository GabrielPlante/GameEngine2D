#include "EntityHandler.h"

#include "../GameEngine2D/TransformComponent.h"

#include "../Map/MapEntityHandler.h"
#include "../Map/HexagonalMap.h"
#include "../Map/PathFinder.h"

#include "MovementComponent.h"
#include "GameValues.h"

namespace ian {
	ge::Entity EntityHandler::createEntity(ge::Vector2<double> position, unsigned int movespeed) {
		//Create the entity
		ge::Entity entityHandle{ ge::Entity::Create({position, 0}) };

		//Create the map entityHandle
		map::MapEntityHandler<gv::tileSize>::createMapEntity(position, entityHandle);

		//Create the movement component and give it to the entity
		MovementComponent movComp{ position, movespeed };
		entityHandle.addComponent(std::move(movComp));

		//Return the entityHandle
		return entityHandle;
	}

	void EntityHandler::setDestination(ge::Entity entityHandle, ge::Vector2<double> destination) {
		//Get the position and destination tile
		ge::Vector2<size_t> positionTile{ map::HexagonalMap::absoluteToRelative(entityHandle.getComponent<ge::TransformComponent>().position, gv::tileWidth, gv::tileHeight) };
		ge::Vector2<size_t> destinationTile{ map::HexagonalMap::absoluteToRelative(destination, gv::tileWidth, gv::tileHeight) };
		//Create the path finder object
		map::PathFinder pathFinder{ positionTile, destinationTile };
		//Compute the path and store it
		entityHandle.getComponent<MovementComponent>().destinationStack = pathFinder.findPath();
	}
}
