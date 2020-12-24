#pragma once
/*#include "../GameEngine2D/IDGenerator.h"
#include "../GameEngine2D/Vector2.h"

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
		//Add an entity to a tile
		static void addEntity(ge::Vector2<double> position, uint32_t id) { MapStorage::modifyTile(getTile(position)).entities.push_back(id); }

		//remove an entity from a tile, return true if the entity is found and deleted 
		static bool removeEntity(ge::Vector2<double> position, uint32_t id);

		//Move an entity to a new tile, return true if the entity is found and moved
		static void moveEntity(uint32_t id, ge::Vector2<double> oldPosition, ge::Vector2<double> newPosition);

		//Get all the entities in the neighborhood of the one given. Garanteed to not return the given entity
		static std::vector<uint32_t> getNeighborEntities(ge::Vector2<double> position, uint32_t id);
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
	bool MapEntityHandler<tileSize>::removeEntity(ge::Vector2<double> position, uint32_t id) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//Search the entity in the tile
		for (auto it = MapStorage::modifyTile(tilePosition).entities.begin(); it != MapStorage::modifyTile(tilePosition).entities.end(); it++) {
			//If found, delete the entity
			if (*it == id) {
				MapStorage::modifyTile(tilePosition)->entities.erase(it);
				return true;
			}
		}
		//If not found, notify the user
		return false;
	}

	template <int tileSize>
	void MapEntityHandler<tileSize>::moveEntity(uint32_t id, ge::Vector2<double> oldPosition, ge::Vector2<double> newPosition) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(oldPosition) };

		//Search the entity in the tile
		for (auto it = MapStorage::modifyTile(tilePosition).entities.begin(); it != MapStorage::modifyTile(tilePosition).entities.end(); it++) {
			//If found, delete the entity
			if (*it == id) {
				MapStorage::modifyTile(tilePosition).entities.erase(it);
				break;
			}
		}

		addEntity(newPosition, id);
	}

	template <int tileSize>
	std::vector<uint32_t> MapEntityHandler<tileSize>::getNeighborEntities(ge::Vector2<double> position, uint32_t id) {
		//Get the tile position
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//The vector that will contain the neighbors
		std::vector<uint32_t> neighborEntities;

		//Add the neighbors within the tile
		std::vector<uint32_t>& entitiesInTile{ MapStorage::modifyTile(tilePosition)->entities };
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

}*/

