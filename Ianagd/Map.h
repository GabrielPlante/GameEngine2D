#pragma once
#include <vector>

#include "../GameEngine2D/Vector2.h"
#include <array>

#include "TileComponent.h"

namespace ian {
	//The map class is used to store the map and provide usefull function to deal with tile
	class Map
	{
	private:
		//The map
		std::array<std::vector<std::vector<TileComponent>>, 4> tileMap;

		//Transform coordinate to the tile index in the vector. The first number of the array is the double vector index in tileMap, the two other are x and y.
		std::array<int, 3> coordinateToTile(ge::Vector2<int> coordinate) const;
	public:
		//Get the coordinate relative to the tile map from an absolute in game position
		ge::Vector2<int> absoluteToRelative(ge::Vector2<int> absoluteCoordinate) const;

		//Get a pointer to the tile
		TileComponent* getTile(ge::Vector2<int> tileCoordinate);

		//Return true if there is a tile existing at the tile coordinate
		bool tileExist(ge::Vector2<int> tileCoordinate) const;

		//Add a tile to the map. If the tile already exist it is replaced. If the tile is not connected to the other it generate empty tile
		void addTile(ge::Vector2<int> tileCoordinate, TileComponent&& tile);

	};

}
