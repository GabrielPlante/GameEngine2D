#pragma once

#include "../GameEngine2D/Vector2.h"

namespace map {
	//The component of an entity on the map
	struct MapEntityComponent
	{
		//The id of the component
		unsigned int id;

		//The entity position
		ge::Vector2<double> position;
	};

	//Implementation here because of the templated class

	/*template <int tileSize>
	MapEntity<tileSize>::MapEntity(ge::Vector2<double> position) {
		setPosition(position);
	}

	template <int tileSize>
	ge::Vector2<double> MapEntity<tileSize>::getPosition() const {
		//Compute the tile dimension
		constexpr double tileWidth{ tileSize * 1.73205080757 };
		constexpr double tileHeight{ tileSize * 2.0 };
		//Get the real tile position (to adapt from the hexagonal grid)
		ge::Vector2<long> realTilePosition{ HexagonalMap::relativeToAbsolute(tilePosition, tileWidth, tileHeight) };
		//Add the position within the tile and return the position
		return ge::Vector2<double>{realTilePosition.x + positionInTile.x, realTilePosition.y + positionInTile.y};
	}

	template <int tileSize>
	void MapEntity<tileSize>::changePosition(ge::Vector2<double> newPosition) {
		removePosition(newPosition);
		setPosition(newPosition);
	}*/
}
