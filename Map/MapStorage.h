#pragma once

#include "../GameEngine2D/VectorOfVector.h"
#include "../GameEngine2D/Vector2.h"

namespace map {
	template <typename TileComponent>
	//Store every tile component that compose the map
	class MapStorage
	{
	private:
		//The map storage, static so the map is unique
		ge::VectorOfVector<TileComponent> map;
	public:
		MapStorage(std::function<bool(const TileComponent&)> isValid);

		//Add a tile to the map. Return true if the tile was added, return false if there was already a tile
		void addTile(ge::Vector2<size_t> position, TileComponent&& tile) { map.addElement(position, std::move(tile)); }

		//Delete the tile at the position. Return true if the tile was deleted, and false if there was no tile at the position
		void deleteTile(ge::Vector2<size_t> position) { map.deleteElement(position); }

		//Check if there is a tile at the position specified, return true if there is one
		bool tileExist(ge::Vector2<size_t> position) const { return map.elementExist(position); }

		//Get a tile
		const TileComponent& getTile(ge::Vector2<size_t> position) const { return map[position]; }

		//Get a posize_ter on the tile
		TileComponent& modifyTile(ge::Vector2<size_t> position) { return map[position]; }

		//The map iterator
		typename ge::VectorOfVector<TileComponent>::Iterator begin() { return map.begin(); }
	};


	template <typename TileComponent>
	MapStorage<TileComponent>::MapStorage(std::function<bool(const TileComponent&)> isValid)
		: map{ []() {return TileComponent; }, isValid }
	{}
}

