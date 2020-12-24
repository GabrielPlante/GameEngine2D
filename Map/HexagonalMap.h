#pragma once

#include "../GameEngine2D/Vector2.h"

#include "MapStorage.h"

namespace map {

	//This class provide method that are usefull when working with an hexagonal map
	namespace HexagonalMap
	{
		//Relative position to an absolute one (ie: from tile coordinate to real coordinate)
		ge::Vector2<long> relativeToAbsolute(ge::Vector2<size_t> relative, double tileWidth, double tileHeight);

		//Absolute position to a relative one (ie: from real coordinate to tile coordinate)
		ge::Vector2<size_t> absoluteToRelative(ge::Vector2<double> absolute, double tileWidth, double tileHeight);

		template <typename TileComponent>
		//Get the 6 neighbors of a tile
		std::vector<TileComponent*> getNeighbors(MapStorage<TileComponent>* mapStorage, ge::Vector2<size_t> position);

		template <typename TileComponent>
		//Get the neighbors of a tile with their position
		std::vector<std::pair<ge::Vector2<size_t>, TileComponent*>> getNeighborsWithPos(MapStorage<TileComponent>* mapStorage, ge::Vector2<size_t> position);

		//Get the distance between two tiles
		int distance(ge::Vector2<int> tile1, ge::Vector2<int> tile2);



		//Function definition

		template <typename TileComponent>
		std::vector<TileComponent*> getNeighbors(MapStorage<TileComponent>* mapStorage, ge::Vector2<size_t> position) {
			std::vector<TileComponent*> neighbors;
			if (mapStorage->tileExist({ position.x + 1, position.y }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x + 1, position.y }));
			if (mapStorage->tileExist({ position.x + 1, position.y - 1 }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x + 1, position.y - 1 }));
			if (mapStorage->tileExist({ position.x, position.y - 1 }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x, position.y - 1 }));
			if (mapStorage->tileExist({ position.x - 1, position.y }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x - 1, position.y }));
			if (mapStorage->tileExist({ position.x - 1, position.y + 1 }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x - 1, position.y + 1 }));
			if (mapStorage->tileExist({ position.x, position.y + 1 }))
				neighbors.push_back(&mapStorage->modifyTile({ position.x, position.y + 1 }));

			return neighbors;
		}

		template <typename TileComponent>
		std::vector<std::pair<ge::Vector2<size_t>, TileComponent*>> getNeighborsWithPos(MapStorage<TileComponent>* mapStorage, ge::Vector2<size_t> position) {
			std::vector<std::pair<ge::Vector2<size_t>, TileComponent*>> neighbors;
			if (mapStorage->tileExist({ position.x + 1, position.y }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x + 1, position.y }, & mapStorage->modifyTile({ position.x + 1, position.y })));
			if (mapStorage->tileExist({ position.x + 1, position.y - 1 }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x + 1, position.y - 1 }, & mapStorage->modifyTile({ position.x + 1, position.y - 1 })));
			if (mapStorage->tileExist({ position.x, position.y - 1 }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x, position.y - 1 }, & mapStorage->modifyTile({ position.x, position.y - 1 })));
			if (mapStorage->tileExist({ position.x - 1, position.y }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x - 1, position.y }, & mapStorage->modifyTile({ position.x - 1, position.y })));
			if (mapStorage->tileExist({ position.x - 1, position.y + 1 }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x - 1, position.y + 1 }, & mapStorage->modifyTile({ position.x - 1, position.y + 1 })));
			if (mapStorage->tileExist({ position.x, position.y + 1 }))
				neighbors.push_back(std::make_pair(ge::Vector2<size_t>{ position.x, position.y + 1 }, & mapStorage->modifyTile({ position.x, position.y + 1 })));

			return neighbors;
		}
	}
}

