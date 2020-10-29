#include "EntityHandler.h"

#include "../GameEngine2D/Storage.h"

#include "../Map/MapEntityHandler.h"
#include "../Map/HexagonalMap.h"
#include "../Map/PathFinder.h"

#include "MovementComponent.h"
#include "GameValues.h"

namespace ian {
	unsigned int EntityHandler::createEntity(ge::Vector2<double> position, unsigned int movespeed) {
		unsigned int mapEntityId{ map::MapEntityHandler<gv::tileSize>::createMapEntity(position) };

		MovementComponent movComp{ mapEntityId, position, position, movespeed };
		return ge::Storage<MovementComponent>::addComponent(std::move(movComp));
	}

	void EntityHandler::setDestination(unsigned int entityId, ge::Vector2<double> destination) {
		//Get the component from the storage
		MovementComponent* component{ ge::Storage<MovementComponent>::getComponent(entityId) };
		//Get the position and destination tile
		ge::Vector2<size_t> positionTile{ map::HexagonalMap::absoluteToRelative(component->position, gv::tileWidth, gv::tileHeight) };
		ge::Vector2<size_t> destinationTile{ map::HexagonalMap::absoluteToRelative(destination, gv::tileWidth, gv::tileHeight) };
		//Create the path finder object
		map::PathFinder pathFinder{ positionTile, destinationTile };
		//Compute the path and store it
		component->destinationStack = pathFinder.findPath();
	}
}
