#include "EntityHandler.h"

#include "../GameEngine2D/Storage.h"

#include "../Map/MapEntityHandler.h"

#include "MovementComponent.h"
#include "GameValues.h"

namespace ian {
	unsigned int EntityHandler::createEntity(ge::Vector2<double> position, unsigned int movespeed) {
		unsigned int mapEntityId{ map::MapEntityHandler<gv::tileSize>::createMapEntity(position) };

		MovementComponent movComp{ mapEntityId, position, position, movespeed };
		return ge::Storage<MovementComponent>::addComponent(std::move(movComp));
	}

	void EntityHandler::setDestination(unsigned int entityId, ge::Vector2<double> destination) {
		ge::Storage<MovementComponent>::getComponent(entityId)->destination = destination;
	}
}
