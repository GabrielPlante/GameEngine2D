#include "MapSystem.h"

#include "../GameEngine2D/Drawer.h"

#include "GameCore.h"
#include "GameValues.h"

namespace ian {
	void MapSystem::renderMap() {

		//Initialise the drawer
		ge::Drawer drawer;

		//Get the camera dimension
		ge::Rectangle cameraRect{ GameCore::getInstance()->getCamera()->getRectangle() };
		previousCameraRectangle = cameraRect;

		//Get the renderer to render to
		SDL_Renderer* renderer{ drawer.startDrawing({cameraRect.w, cameraRect.h}, ge::Color{}) };

		Map* mapPtr{ &GameCore::getInstance()->getFactoryFactory()->map };

		//There might be a better system to check if there is every tile in the camera
		for (int i = cameraRect.x; i < cameraRect.x + cameraRect.w + (cameraRect.w % tileSize); i += tileSize) {
			for (int j = cameraRect.y; j < cameraRect.y + cameraRect.h + (cameraRect.h % tileSize); j += tileSize) {
				//If the tile doesn't exist, we create it
				if (!mapPtr->tileExist(mapPtr->absoluteToRelative({ i, j }))) {
					TileComponent tile;
					tile.color = { 0, 255, 0 };
					mapPtr->addTile(mapPtr->absoluteToRelative({ i, j }), std::move(tile));
				}
				ge::Color tileColor = mapPtr->getTile(mapPtr->absoluteToRelative({ i, j }))->color;
				SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(tileColor.red), static_cast<Uint8>(tileColor.green), static_cast<Uint8>(tileColor.blue), static_cast<Uint8>(tileColor.alpha));
				SDL_Rect tileRect = ge::Rectangle{ i - cameraRect.x, j - cameraRect.y, tileSize, tileSize }.toSDL_Rect();
				SDL_RenderFillRect(renderer, &tileRect);
			}
		}
		F_FACTORY->rendererFactory.getComponent(mapRendererId)->setTexture(drawer.finishDrawing());
		F_FACTORY->rendererFactory.getComponent(mapRendererId)->size = ge::Vector2<int>{ cameraRect.w, cameraRect.h };
		F_FACTORY->positionFactory.getComponent(F_FACTORY->rendererFactory.getComponent(mapRendererId)->positionComponentId)->position = ge::Vector2<>{ cameraRect.x, cameraRect.y };
	}

	void MapSystem::update() {
		if (!(GameCore::getInstance()->getCamera()->getRectangle() == previousCameraRectangle))
			renderMap();

	}
}
