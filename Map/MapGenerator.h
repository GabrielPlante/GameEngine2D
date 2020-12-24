#pragma once
#include <vector>
#include <memory>

#include "../GameEngine2D/ShapeCreator.h"
#include "../GameEngine2D/Color.h"

#include "HexagonalMap.h"
#include "MapStorage.h"

namespace map {
	template <typename TileComponent>
	//Generate a map of a given size with tile of a given and color
	void generateMap(MapStorage<TileComponent>* mapStorage, int mapSize, ge::Color color);

	template <typename TileComponent, int tileSize>
	//Generate the texture of the created map
	void generateMapTexture(MapStorage<TileComponent>* mapStorage, std::shared_ptr<ge::HexagonBatch> batch);



	//Function definition

	template <typename TileComponent>
	void generateMap(MapStorage<TileComponent>* mapStorage, int mapSize, ge::Color color) {
		//For every tile
		for (size_t i = 0; i <= 2 * mapSize; i++) {
			for (size_t j = 0; j <= 2 * mapSize; j++) {
				if (i + j >= mapSize && i + j <= 3 * mapSize) {
					TileComponent tile;
					tile.isInit = true;
					tile.color = color;
					mapStorage->addTile({ i, j }, std::move(tile));
				}
			}
		}
	}

	template <typename TileComponent, int tileSize>
	void generateMapTexture(MapStorage<TileComponent>* mapStorage, std::shared_ptr<ge::HexagonBatch> batch)
	{
		std::vector<ge::HexagonTransform> hexagons;
		for (auto it = mapStorage->begin(); !it.endReached(); it++) {
			hexagons.push_back({ HexagonalMap::relativeToAbsolute(it.getPosition()), tileSize, it->color });
		}
		ge::createHexagons(batch, hexagons);
	}
}
