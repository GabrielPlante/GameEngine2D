#pragma once
#include "../GameEngine2D/IDGenerator.h"
#include "../GameEngine2D/Vector2.h"

#include "MapEntityComponent.h"

namespace map {
	template <int tileSize>
	//MapEntityHandler is used to handle map entity in the map storage. It allow an opaque way of storing the entity's position
	class MapEntityHandler
	{
	private:
		static ge::IDGenerator<unsigned int> idGenerator;

		//Get the tile out of a position
		static ge::Vector2<size_t> getTile(ge::Vector2<double> position);
	public:
		//Create a map entity at a certain position, return the id of the map entity
		static unsigned int createMapEntity(ge::Vector2<double> position);

		//Delete an entity, return true if the entity is found and deleted
		static bool deleteEntity(ge::Vector2<double> position, unsigned int id);

		//Move an entity to a new place, return true if the entity is found and moved
		static void moveEntity(ge::Vector2<double> oldPosition, unsigned int id, ge::Vector2<double> newPosition);

		//Get all the entities in the neighborhood of the one given. Garanteed to not return the given entity
		static std::vector<MapEntityComponent> getNeighborEntities(ge::Vector2<double> position, unsigned int id);
	};
}

