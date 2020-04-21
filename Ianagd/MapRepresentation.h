#pragma once
#include <array>

#include "../GameEngine2D/Vector2.h"

#include "Map.h"

namespace ian {
	constexpr int borderTile{ 0 };
	constexpr int walkableTile{ 1 };

	template <int Height, int Width>
	class MapRepresentation
	{
	private:
		ge::Vector2<int> mapCoordinate;

		std::array<std::array<int, Width>, Height> mapArray;

		TileComponent getTile(int tile) const;

	public:
		//Constructor
		MapRepresentation(ge::Vector2<int> mapCoordinate, std::array<std::array<int, Width>, Height> mapArray)
			: mapCoordinate{ mapCoordinate }, mapArray{ mapArray } {}

		//Transfert this map to the actual in game map
		void transfertToMap(Map* map) const;
	};

	template<int W, int H>
	void MapRepresentation<W, H>::transfertToMap(Map* map) const {
		for (int i = 0; i != W; i++) {
			for (int j = 0; j != H; j++) {
				map->addTile({ i + mapCoordinate.x, j + mapCoordinate.y }, getTile(mapArray[i][j]));
			}
		}
	}

	template<int W, int H>
	TileComponent MapRepresentation<W, H>::getTile(int tileType) const {
		TileComponent tile;
		switch (tileType)
		{
		case borderTile:
			tile.isWalkable = false;
			tile.color = { 100, 100, 100 };
			break;
		case walkableTile:
			tile.isWalkable = true;
			tile.color = { 0, 128, 0 };
			break;
		default:
			break;
		}
		return tile;
	}


	/*template <typename W>
	template <typename H>
	void MapRepresentation<W, H>::transfertToMap(Map* map) const {

	}*/
}

