#include "Map.h"

#include "GameValues.h"

namespace ian {
	std::array<int, 3> Map::coordinateToTile(ge::Vector2<int> coordinate) const {
		//The 0 tile is in the positive vector, so the negative vector start at the tile -1.
		//To avoid wasting 1 tile space on every negative vector, the negative coordinate is reduced by one.
		if (coordinate.x >= 0) {
			if (coordinate.y >= 0)
				return { 0, coordinate.x, coordinate.y };
			else
				return { 1, coordinate.x, abs(coordinate.y) - 1 };
		}
		else {
			if (coordinate.y >= 0) {
				return { 2, abs(coordinate.x) - 1, coordinate.y };
			}
			else
				return { 3, abs(coordinate.x) - 1, abs(coordinate.y) - 1 };
		}
	}

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

	TileComponent* Map::getTile(ge::Vector2<int> tileCoordinate) {
		std::array<int, 3> actualCoordinate{ coordinateToTile(tileCoordinate) };
		return &tileMap[actualCoordinate[0]][actualCoordinate[1]][actualCoordinate[2]];
	}

	bool Map::tileExist(ge::Vector2<int> tileCoordinate) const {
		std::array<int, 3> actualCoordinate{ coordinateToTile(tileCoordinate) };
		return tileMap[actualCoordinate[0]].size() > actualCoordinate[1] && tileMap[actualCoordinate[0]][actualCoordinate[1]].size() > actualCoordinate[2];
	}

	void Map::addTile(ge::Vector2<int> tileCoordinate, TileComponent&& tile) {
		std::array<int, 3> coordinate{ coordinateToTile(tileCoordinate) };
		//Make sure the x coordinate is big enough for the new tile
		while (tileMap[coordinate[0]].size() <= coordinate[1]) {
			std::vector<TileComponent> vector;
			tileMap[coordinate[0]].push_back(vector);
		}
		//Make sure the y coordinate is big enough for the new tile
		while (tileMap[coordinate[0]][coordinate[1]].size() <= coordinate[2]) {
			TileComponent tempTile;
			tileMap[coordinate[0]][coordinate[1]].push_back(tempTile);
		}
		//Add the new tile
		tileMap[coordinate[0]][coordinate[1]][coordinate[2]] = tile;
	}
}
