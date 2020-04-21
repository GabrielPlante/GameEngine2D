#include "Map.h"

#include "GameValues.h"

namespace ian {

	ge::Vector2<int> Map::absoluteToRelative(ge::Vector2<> coordinate) const {
		//The minus one here is to distinguish the -tileSize | 0 tile and the 0 | tileSize tile.
		if (coordinate.x >= 0)
			coordinate.x /= tileSize;
		else
			coordinate.x = (coordinate.x + 1) / tileSize - 1;
		if (coordinate.y >= 0)
			coordinate.y /= tileSize;
		else
			coordinate.y = (coordinate.y + 1) / tileSize - 1;
		return { static_cast<int>(coordinate.x), static_cast<int>(coordinate.y) };
	}

	ge::Vector2<> Map::relativeToAbsolute(ge::Vector2<int> coordinate) const {
		return { coordinate.x * tileSize, coordinate.y * tileSize };
	}

	void Map::addTile(ge::Vector2<int> tileCoordinate, TileComponent&& tile) {
		tileMap.insert(std::pair<ge::Vector2<int>, TileComponent>(tileCoordinate, tile));
	}
}
