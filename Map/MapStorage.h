#pragma once
#include <map>

#include "../GameEngine2D/VectorOfVector.h"
#include "../GameEngine2D/Vector2.h"

#include "TileComponent.h"

namespace map {
	//Store every tile component that compose the map
	class MapStorage
	{
	private:
		//The map storage, static so the map is unique
		static ge::VectorOfVector<TileComponent> map;
	public:
		//Add a tile to the map. Return true if the tile was added, return false if there was already a tile
		void addTile(ge::Vector2<int> position, TileComponent&& tile) { map.addElement(position, std::move(tile)); }

		//Delete the tile at the position. Return true if the tile was deleted, and false if there was no tile at the position
		void deleteTile(ge::Vector2<int> position) { map.deleteElement(position); }

		//Check if there is a tile at the position specified, return true if there is one
		bool tileExist(ge::Vector2<int> position) const { return map.elementExist(position); }

		//Get a tile
		const TileComponent& getTile(ge::Vector2<int> position) const { return map[position]; }

		//Get a pointer on the tile
		TileComponent* modifyTile(ge::Vector2<int> position) { return &map[position]; }

		//The map iterator
		ge::VectorOfVector<TileComponent>::Iterator getBeginningIterator() { return map.begin(); }
	};
}

