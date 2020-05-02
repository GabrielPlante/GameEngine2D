#include "MapSystem.h"

#include "../GameEngine2D/Drawer.h"
#include "../GameEngine2D/Camera.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

#include <iostream>

namespace ian {
	void MapSystem::renderMap() {

		//Get the camera dimension
		ge::Rectangle cameraRect{ GameCore::getInstance()->getCamera()->getRectangle() };
		previousCameraRectangle = cameraRect;

		//Here we make sure that we position our rendering rectangle at top left corner of the tile that is in the top left corner of the screen
		const int cameraOffsetX{ cameraRect.x % gv::tileSize };
		const int cameraOffsetY{ cameraRect.y % gv::tileSize };
		ge::Vector2<> position{ cameraRect.x - (cameraRect.x < 0 ? gv::tileSize + cameraOffsetX : cameraOffsetX), cameraRect.y - (cameraRect.y < 0 ? gv::tileSize + cameraOffsetY : cameraOffsetY) };

		ge::Rectangle scene{ position, cameraRect.w + gv::tileSize * 3 / 2, cameraRect.h + gv::tileSize * 3 / 2 };

		//Initialise the drawer
		ge::Drawer drawer;

		//Get the renderer to render to
		SDL_Renderer* renderer{ drawer.startDrawing({scene.w, scene.h}, ge::Color{}) };

		Map* mapPtr{ &GameCore::getInstance()->getFactoryFactory()->map };


		//There might be a better system to check if there is every tile in the camera
		int relativePositionX{ 0 };
		for (int i = scene.x; i < scene.x + scene.w; i += gv::tileSize) {
			int relativePositionY{ 0 };
			for (int j = scene.y; j < scene.y + scene.h; j += gv::tileSize) {
				ge::Color tileColor{ 0, 0, 0 };
				//If a tile exist here, we take it's color, else it's black
				if (mapPtr->tileExist(mapPtr->absoluteToRelative({ i, j }))) {
					tileColor = mapPtr->getTile(mapPtr->absoluteToRelative({ i, j })).color;
				}
				//Set the right render color
				SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(tileColor.red), static_cast<Uint8>(tileColor.green), static_cast<Uint8>(tileColor.blue), static_cast<Uint8>(tileColor.alpha));
				//Render the tile
				SDL_Rect tileRect = ge::Rectangle{ relativePositionX, relativePositionY, gv::tileSize, gv::tileSize }.toSDL_Rect();
				SDL_RenderFillRect(renderer, &tileRect);

				relativePositionY += gv::tileSize;
			}
			relativePositionX += gv::tileSize;
		}
		//Update the texture component
		F_FACTORY->rendererFactory.getComponent(mapRendererId)->texture = (drawer.finishDrawing());
		F_FACTORY->positionFactory.getComponent(F_FACTORY->rendererFactory.getComponent(mapRendererId)->positionComponentId)->setPosition(position);

		//SDL_SetTextureBlendMode(F_FACTORY->rendererFactory.getComponent(mapRendererId)->texture.get(), SDL_BLENDMODE_NONE);
	}

	void MapSystem::update() {
		if (F_FACTORY->gameComponent.graphicsOn && !(GameCore::getInstance()->getCamera()->getRectangle() == previousCameraRectangle)) {
			renderMap();
		}
	}
}
