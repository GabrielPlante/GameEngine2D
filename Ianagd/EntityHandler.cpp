#include "EntityHandler.h"

#include "../GameEngine2D/Entity.h"

#include "../Map/MapEntityHandler.h"
#include "../Map/HexagonalMap.h"
#include "../Map/PathFinder.h"

#include "MovementComponent.h"
#include "GameValues.h"

namespace ian {
	unsigned int EntityHandler::createEntity(ge::Vector2<double> position, unsigned int movespeed) {
		//Create the entity
		ge::EntityHandle entityHandle{ ge::Entity::Create() };

		//Create the map entityHandle
		map::MapEntityHandler<gv::tileSize>::createMapEntity(position, entityHandle);

		//Create the movement component and give it to the entity
		MovementComponent movComp{ entityHandle, position, position, movespeed };
		entityHandle.addComponent(std::move(movComp));

		//Return the entityHandle
		return entityHandle;
	}

	void EntityHandler::setDestination(unsigned int entityId, ge::Vector2<double> destination) {
		//Get the component from the storage
		MovementComponent& component{ ge::Storage<MovementComponent>::get(entityId) };
		//Get the position and destination tile
		ge::Vector2<size_t> positionTile{ map::HexagonalMap::absoluteToRelative(component.position, gv::tileWidth, gv::tileHeight) };
		ge::Vector2<size_t> destinationTile{ map::HexagonalMap::absoluteToRelative(destination, gv::tileWidth, gv::tileHeight) };
		//Create the path finder object
		map::PathFinder pathFinder{ positionTile, destinationTile };
		//Compute the path and store it
		component.destinationStack = pathFinder.findPath();
	}
}
