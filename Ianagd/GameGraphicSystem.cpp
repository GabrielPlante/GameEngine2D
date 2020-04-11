#include "GameGraphicSystem.h"

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Rectangle.h"

#include "FactoryFactory.h"

namespace ian {
	GameGraphicSystem::GameGraphicSystem(int screenWidth, int screenHeight, FactoryFactory* factoryFactory)
		: window{ screenWidth, screenHeight }, factoryFactory{ factoryFactory }
	{

	}

	void GameGraphicSystem::update() {
		window.clear();

		//Every other update goes here

		//Update every renderer associated with an entity
		for (auto it = factoryFactory->rendererComponentFactory.getBeginningIterator(); it != factoryFactory->rendererComponentFactory.getEndIterator(); it++) {
			SDL_Rect dstRect = ge::Rectangle{ it->owner->getPosition(), it->size.x, it->size.y }.toSDL_Rect();
			SDL_RenderCopy(window.getRenderer(), it->texture, it->srcRect, &dstRect);
			//ge::CONSOLE_LOG(std::to_string(it->owner->getPosition().x)+" "+std::to_string(it->owner->getPosition().y));
		}

		//Update and render the console
		ge::Console::getInstance()->update(window.getRenderer());
		//The console doesn't show itself automaticaly if it's not open
		ge::Console::getInstance()->render(window.getRenderer());

		window.render();
	}
}
