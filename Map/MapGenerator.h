#pragma once

#include "../GameEngine2D/Color.h"

#include "../GameEngine2D/TextureWrapper.h"

namespace map {
	class MapGenerator
	{
	public:
		//Generate a map of a given size with tile of a given and color
		static void generate(int mapSize, ge::Color color);

		static ge::TextureWrapper generateTexture(int tileSize, ge::Vector2<int> mapSize);
	};
}

