#include "MapGenerator.h"

#include "../GameEngine2D/HexagonCreator.h"
#include "../GameEngine2D/Drawer.h"

#include "TileComponent.h"
#include "HexagonalMap.h"
#include "MapStorage.h"

namespace map {
	void MapGenerator::generate(int mapSize, ge::Color color) {
		MapStorage storage;
		//For every tile
		for (int i = 0; i <= 2 * mapSize; i++) {
			for (int j = 0; j <= 2 * mapSize; j++) {
				if (i + j >= mapSize && i + j <= 3 * mapSize) {
					TileComponent tile;
					tile.isInit = true;
					tile.color = color;
					storage.addTile({ i, j }, std::move(tile));
				}
			}
		}
	}

	ge::TextureWrapper MapGenerator::generateTexture(int tileSize, ge::Vector2<int> mapSize) {

		//Compute the tile dimension
		const double tileWidth{ tileSize * sqrt(3.0) };
		const double tileHeight{ tileSize * 2.0 };

		//Create the base hexagon. Only the color of this hexagon will be changed to render every other hexagon
		ge::TextureWrapper baseHexagon{ ge::HexagonCreator{tileSize, {255, 255, 255}}.getTexture() };

		//Create the drawer and get the renderer
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({mapSize.x, mapSize.y}, {0, 0, 0}) };

		MapStorage storage;
		for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {

			//Set the right color
			SDL_SetTextureColorMod(baseHexagon.get(), it->color.red, it->color.green, it->color.blue);

			//Create the coordinate
			ge::Vector2<> pos{ HexagonalMap::relativeToAbsolute(it.getPosition(), tileWidth, tileHeight) };
			ge::Vector2<int> posInt{ static_cast<int>(pos.x),  static_cast<int>(pos.y) };

			//Render the tile
			baseHexagon.render(renderer, posInt);
		}

		return drawer.finishDrawing();
	}
}
