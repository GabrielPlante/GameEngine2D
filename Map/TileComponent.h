#pragma once
#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Color.h"

#include "MapEntityComponent.h"

namespace map {
	//Hold every information about a tile
	struct TileComponent {
		//Is the tile initialised
		bool isInit{ false };

		//The tile color
		ge::Color color;

		//The entities in the tile
		std::vector<MapEntityComponent> entities;
	};
}
