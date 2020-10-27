#include "MapEntityHandler.h"

#include "HexagonalMap.h"
#include "MapStorage.h"

namespace map {
	template <int tileSize>
	ge::IDGenerator<unsigned int> MapEntityHandler<tileSize>::idGenerator{};

	template <int tileSize>
	ge::Vector2<size_t> MapEntityHandler<tileSize>::getTile(ge::Vector2<double> position) {
		//Compute the tile dimension
		constexpr double tileWidth{ tileSize * 1.73205080757 };
		constexpr double tileHeight{ tileSize * 2.0 };
		//Get the tile position of the new entity
		return HexagonalMap::absoluteToRelative(position, tileWidth, tileHeight);
	}

	template <int tileSize>
	unsigned int MapEntityHandler<tileSize>::createMapEntity(ge::Vector2<double> position) {
		//Compute the tile dimension
		ge::Vector2<size_t> tilePosition{ getTile(position) };

		//Create the component
		MapEntityComponent entity{ idGenerator.getNewID(), position };

		//Get the id
		unsigned int entityId{ entity.id };

		//Add the component to the storage
		MapStorage storage;
		storage.modifyTile(tilePosition)->entities.push_back(std::move(entity));

		return entityId;
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
				idGenerator.deleteID(id);
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