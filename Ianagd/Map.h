#pragma once
#include <map>

#include "../GameEngine2D/Vector2.h"

#include "TileComponent.h"

namespace ian {
	//The map class is used to store the map and provide usefull function to deal with tile
	class Map
	{
	private:
		//The map
		std::map<ge::Vector2<int>, TileComponent> tileMap;

	public:
		//Get the coordinate relative to the tile map from an absolute in game position
		ge::Vector2<int> absoluteToRelative(ge::Vector2<> absoluteCoordinate) const;

		//Get an absolute in game position with a position relative to the tile map
		ge::Vector2<> relativeToAbsolute(ge::Vector2<int> relativeCoordinate) const;

		//Get a pointer to the tile
		const TileComponent& getTile(ge::Vector2<int> tileCoordinate) const { return tileMap.find(tileCoordinate)->second; }

		//Return true if there is a tile existing at the tile coordinate
		bool tileExist(ge::Vector2<int> tileCoordinate) const { return tileMap.find(tileCoordinate) != tileMap.end(); }

		//Add a tile to the map. If the tile already exist it is replaced. If the tile is not connected to the other it generate empty tile
		void addTile(ge::Vector2<int> tileCoordinate, TileComponent&& tile);

	};
}
