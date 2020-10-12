#pragma once

#include "../GameEngine2D/Vector2.h"

namespace map {
	struct TileComponent;

	//This class provide method that are usefull when working with an hexagonal map
	class HexagonalMap
	{
	private:
		//The constructor is private
		HexagonalMap() {}
	public:
		//Relative position to an absolute one
		static ge::Vector2<long> relativeToAbsolute(ge::Vector2<int> relative, double tileWidth, double tileHeight);

		//Absolute position to a relative one
		//ge::Vector2<int> absoluteToRelative(ge::Vector2<> absolute) const;

		//Get the 6 neighbors of a tile
		static std::vector<TileComponent*> getNeighbors(ge::Vector2<int> position);

		//Get the neighbors of a tile with their position
		static std::vector<std::pair<ge::Vector2<int>, TileComponent*>> getNeighborsWithPos(ge::Vector2<int> position);

		//Get the distance between two tiles
		static int distance(ge::Vector2<int> tile1, ge::Vector2<int> tile2);
	};
}

