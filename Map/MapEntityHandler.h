#pragma once
#include "../GameEngine2D/IDGenerator.h"
#include "../GameEngine2D/Vector2.h"

#include "MapEntityComponent.h"
#include "HexagonalMap.h"
#include "MapStorage.h"

namespace map {
	template <int tileSize>
	//MapEntityHandler is used to handle map entity in the map storage. It allow an opaque way of storing the entity's position
	class MapEntityHandler
	{
	private:
		//Get the tile out of a position
		static ge::Vector2<size_t> getTile(ge::Vector2<double> position);
	public:
		//Create a map entity at a certain position, return the id of the map entity
		static void createMapEntity(ge::Vector2<double> position, unsigned int id);

		//Delete an entity, return true if the entity is found and deleted
		static bool deleteEntity(ge::Vector2<double> position, unsigned int id);

		//Move an entity to a new place, return true if the entity is found and moved
		static void moveEntity(ge::Vector2<double> oldPosition, unsigned int id, ge::Vector2<double> newPosition);

		//Get all the entities in the neighborhood of the one given. Garanteed to not return the given entity
		static std::vector<MapEntityComponent> getNeighborEntities(ge::Vector2<double> position, unsigned int id);
	};

	//Definition here because of templated class

	template <int tileSize>
	ge::Vector2<size_t> MapEntityHandler<tileSize>::getTile(ge::Vector2<double> position) {
		//Compute the tile dimension
		constexpr double tileWidth{ tileSize * 1.73205080757 };
		constexpr double tileHeight{ tileSize * 2.0 };
		//Get the tile position of the new entity
		return HexagonalMap::absoluteToRelative(position, tileWidth, tileHeight);
	}

	template <int tileSize>
	void MapEntityHandler<tileSize>::createMapEntity(ge::Vector2<double> position, unsigned int id) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//Create the component
		MapEntityComponent entity{ id, position };

		//Add the component to the storage
		MapStorage storage;
		storage.modifyTile(tilePosition)->entities.push_back(std::move(entity));
	}

	template <int tileSize>
	bool MapEntityHandler<tileSize>::deleteEntity(ge::Vector2<double> position, unsigned int id) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//Search the entity in the tile
		MapStorage storage;
		for (auto it = storage.modifyTile(tilePosition)->entities.begin(); it != storage.modifyTile(tilePosition)->entities.end(); it++) {
			//If found, delete the entity
			if (it->id == id) {
				storage.modifyTile(tilePosition)->entities.erase(it);
				return true;
			}
		}
		//If not found, notify the user
		return false;
	}

	template <int tileSize>
	void MapEntityHandler<tileSize>::moveEntity(ge::Vector2<double> oldPosition, unsigned int id, ge::Vector2<double> newPosition) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(oldPosition) };

		//Search the entity in the tile
		MapStorage storage;
		for (auto it = storage.modifyTile(tilePosition)->entities.begin(); it != storage.modifyTile(tilePosition)->entities.end(); it++) {
			//If found, delete the entity
			if (it->id == id) {
				storage.modifyTile(tilePosition)->entities.erase(it);
				break;
			}
		}

		//Get the new tile position
		tilePosition = getTile(newPosition);

		//Create the component
		MapEntityComponent entity{ id, newPosition };

		//Add the component to the storage
		storage.modifyTile(tilePosition)->entities.push_back(std::move(entity));
	}

	template <int tileSize>
	std::vector<MapEntityComponent> MapEntityHandler<tileSize>::getNeighborEntities(ge::Vector2<double> position, unsigned int id) {
		//Get the tile position
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//The vector that will contain the neighbors
		std::vector<MapEntityComponent> neighborEntities;

		//Add the neighbors within the tile
		MapStorage storage;
		std::vector<MapEntityComponent>& entitiesInTile{ storage.modifyTile(tilePosition)->entities };
		for (int i = 0; i != entitiesInTile.size(); i++) {
			if (entitiesInTile[i].id != id) {
				neighborEntities.push_back(entitiesInTile[i]);
			}
		}

		//Get the neighbors tile
		std::vector<TileComponent*> neighborsTile{ HexagonalMap::getNeighbors(tilePosition) };
		//Get the neighbors entities out of those tiles
		for (auto it = neighborsTile.begin(); it != neighborsTile.end(); it++) {
			for (int i = 0; i != (**it).entities.size(); i++) {
				neighborEntities.push_back((**it).entities[i]);
			}
		}

		//Return the neighbors entities
		return neighborEntities;
	}

}

