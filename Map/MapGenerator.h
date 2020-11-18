#pragma once

#include "../GameEngine2D/Color.h"

namespace map {
	class MapGenerator
	{
	public:
		//Generate a map of a given size with tile of a given and color
		static void generate(int mapSize, ge::Color color);
	};
}

