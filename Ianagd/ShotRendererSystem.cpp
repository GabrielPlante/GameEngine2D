#include "ShotRendererSystem.h"

#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {

	void ShotRendererSystem::update() {
		for (auto it = F_FACTORY->shotRendererFactory.getBeginningIterator(); it != F_FACTORY->shotRendererFactory.getEndIterator(); it++) {
			ge::Vector2<int> size{ F_FACTORY->rendererFactory.getComponent(it->rendererCompId)->getSize() };

			SDL_SetTextureAlphaMod(F_FACTORY->rendererFactory.getComponent(it->rendererCompId)->texture.get(), it->alpha);

			//Decrement the alpha
			it->alpha -= 5;
		}
	}
}
