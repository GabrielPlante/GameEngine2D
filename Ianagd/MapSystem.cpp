#include "MapSystem.h"

#include "../GameEngine2D/Drawer.h"
#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

#include <iostream>

namespace ian {
	void MapSystem::renderMap() {

		//Initialise the drawer
		ge::Drawer drawer;

		//Get the camera dimension
		ge::Rectangle cameraRect{ GameCore::getInstance()->getCamera()->getRectangle() };
		previousCameraRectangle = cameraRect;

		const int cameraOffsetX{ cameraRect.x % tileSize };
		const int cameraOffsetY{ cameraRect.y % tileSize };
		ge::Vector2<> position{ cameraRect.x - (cameraRect.x < 0 ? tileSize + cameraOffsetX : cameraOffsetX), cameraRect.y - (cameraRect.y < 0 ? tileSize + cameraOffsetY : cameraOffsetY) };

		ge::Rectangle scene{ position, cameraRect.w + tileSize, cameraRect.h + tileSize };

		//Get the renderer to render to
		SDL_Renderer* renderer{ drawer.startDrawing({scene.w, scene.h}, ge::Color{}) };

		Map* mapPtr{ &GameCore::getInstance()->getFactoryFactory()->map };

		//There might be a better system to check if there is every tile in the camera
		int relativePositionX{ 0 };
		for (int i = scene.x; i < scene.x + scene.w; i += tileSize) {
			int relativePositionY{ 0 };
			for (int j = scene.y; j < scene.y + scene.h; j += tileSize) {
				//If the tile doesn't exist, we create it
				if (!mapPtr->tileExist(mapPtr->absoluteToRelative({ i, j }))) {
					TileComponent tile;
					tile.color = { 0, 128, 0 };
					mapPtr->addTile(mapPtr->absoluteToRelative({ i, j }), std::move(tile));
				}
				ge::Color tileColor = mapPtr->getTile(mapPtr->absoluteToRelative({ i, j }))->color;
				SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(tileColor.red), static_cast<Uint8>(tileColor.green), static_cast<Uint8>(tileColor.blue), static_cast<Uint8>(tileColor.alpha));
				SDL_Rect tileRect = ge::Rectangle{ relativePositionX, relativePositionY, tileSize, tileSize }.toSDL_Rect();
				SDL_RenderFillRect(renderer, &tileRect);
				relativePositionY += tileSize;
			}
			relativePositionX += tileSize;
		}
		F_FACTORY->rendererFactory.getComponent(mapRendererId)->setTexture(drawer.finishDrawing());
		F_FACTORY->rendererFactory.getComponent(mapRendererId)->size = ge::Vector2<int>{ scene.w, scene.h };
		F_FACTORY->positionFactory.getComponent(F_FACTORY->rendererFactory.getComponent(mapRendererId)->positionComponentId)->position = position;
	}

	void MapSystem::update() {
		if (!(GameCore::getInstance()->getCamera()->getRectangle() == previousCameraRectangle))
			renderMap();

	}
}
