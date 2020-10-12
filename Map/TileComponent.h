#pragma once
#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Color.h"

namespace map {
	//Hold every information about a tile
	struct TileComponent {
		//Is the tile initialised
		bool isInit{ false };

		//The tile color
		ge::Color color;
	};
}
