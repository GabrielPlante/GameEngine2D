#include "GameGraphicSystem.h"
#include <SDL.h>

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Rectangle.h"

#include "RendererComponent.h"
#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	SDL_Rect transformRect(ge::Rectangle rect) {
		rect.resize(GameCore::getInstance()->getCamera()->getZoom());
		ge::Vector2<long> relativePos{ GameCore::getInstance()->getCamera()->absoluteToRelative(rect.x, rect.y) };
		rect.x = relativePos.x;
		rect.y = relativePos.y;
		return rect.toSDL_Rect();
	}

	GameGraphicSystem::GameGraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GameGraphicSystem::update() {
		window.clear();

		//Every other update goes here

		//Update every renderer associated with an entity
		for (auto it = F_FACTORY->rendererFactory.getBeginningIterator(); it != F_FACTORY->rendererFactory.getEndIterator(); it++) {
			//Get the position of the component
			ge::Vector2<> itPosition{ F_FACTORY->positionFactory.getComponent(it->positionComponentId)->getPosition() };
			//Create his destination rectangle (ie where it is on the map) and take his size
			ge::Rectangle dstRect{ itPosition.x - gv::tileSize / 2, itPosition.y - gv::tileSize / 2 , it->getSize().x, it->getSize().y };
			//If the position is in the renderer, we draw it
			if (GameCore::getInstance()->getCamera()->isInCamera(dstRect) && it->texture.get() != nullptr) {
				SDL_Rect sdlDstRect{ transformRect(dstRect) };
				SDL_RenderCopy(window.getRenderer(), it->texture.get(), it->srcRect, &sdlDstRect);
			}
		}

		//Render the health bars in red
		SDL_SetRenderDrawColor(window.getRenderer(), static_cast<Uint8>(255), 0, 0, static_cast<Uint8>(255));
		for (auto it = F_FACTORY->healthFactory.getBeginningIterator(); it != F_FACTORY->healthFactory.getEndIterator(); it++) {
			//Get the position of the component
			ge::Vector2<> itPosition{ F_FACTORY->positionFactory.getComponent(it->positionComponentId)->getPosition() };
			//Create his destination rectangle (ie where it is on the map) and take his size
			ge::Rectangle dstRect{ itPosition.x - gv::tileSize / 2, itPosition.y - gv::tileSize, gv::tileSize * it->health / it->maxHealth, gv::tileSize / 10 };
			if (GameCore::getInstance()->getCamera()->isInCamera(dstRect)) {
				SDL_Rect sdlDstRect{ transformRect(dstRect) };
				SDL_RenderFillRect(window.getRenderer(), &sdlDstRect);
			}
		}

		//Render the UI just before the console
		for (auto it = F_FACTORY->uiFactory.getBeginningIterator(); it != F_FACTORY->uiFactory.getEndIterator(); it++) {
			if (it->texture.get() != nullptr) {
				ge::Vector2<> texturePos{ F_FACTORY->positionFactory.getComponent(it->positionComponentId)->getPosition() };
				SDL_Rect textureRect{ ge::Rectangle{texturePos, it->getSize().x, it->getSize().y}.toSDL_Rect() };
				SDL_RenderCopy(window.getRenderer(), it->texture.get(), NULL, &textureRect);
			}
		}

		//Update and render the console
		ge::Console::getInstance()->update(window.getRenderer());
		//The console doesn't show itself automaticaly if it's not open
		ge::Console::getInstance()->render(window.getRenderer());

		window.render();
	}
}
