#include "GameGraphicSystem.h"
#include <SDL.h>

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Rectangle.h"

#include "FactoryFactory.h"
#include "RendererComponent.h"
#include "GameCore.h"

namespace ian {
	GameGraphicSystem::GameGraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GameGraphicSystem::update() {
		window.clear();

		//Every other update goes here

		//Update every renderer associated with an entity
		for (auto it = F_FACTORY->rendererFactory.getBeginningIterator(); it != F_FACTORY->rendererFactory.getEndIterator(); it++) {
			ge::Rectangle dstRect{ F_FACTORY->positionFactory.getComponent(it->positionComponentId)->position, it->size.x, it->size.y };
			if (GameCore::getInstance()->getCamera()->isInCamera(dstRect) && it->texture.get() != nullptr) {
				dstRect.resize(GameCore::getInstance()->getCamera()->getZoom());
				ge::Vector2<long> relativePos{ GameCore::getInstance()->getCamera()->absoluteToRelative(dstRect.x, dstRect.y) };
				dstRect.x = relativePos.x;
				dstRect.y = relativePos.y;
				SDL_Rect sdlDstRect = dstRect.toSDL_Rect();
				SDL_RenderCopy(window.getRenderer(), it->texture.get(), it->srcRect, &sdlDstRect);
			}
		}

		//Update and render the console
		ge::Console::getInstance()->update(window.getRenderer());
		//The console doesn't show itself automaticaly if it's not open
		ge::Console::getInstance()->render(window.getRenderer());

		window.render();
	}
}
