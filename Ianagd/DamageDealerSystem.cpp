#include "DamageDealerSystem.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	unsigned int createShot(ge::Vector2<> startPosition, ge::Vector2<> endPosition) {
		ge::Vector2<int> size{ abs(startPosition.x - endPosition.x), abs(startPosition.y - endPosition.y) };
		if (startPosition.x == endPosition.x)
			size.x += 3;
		else if (startPosition.y == endPosition.y)
			size.y += 3;

		//Draw the shot
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing(size, {0, 0, 255}) };
		if (startPosition.x > endPosition.x && startPosition.y > endPosition.y || startPosition.x < endPosition.x && startPosition.y < endPosition.y) {
			SDL_RenderDrawLine(renderer, 0, 0, size.x, size.y);
			SDL_RenderDrawLine(renderer, 1, 0, size.x, size.y - 1);
			SDL_RenderDrawLine(renderer, 0, 1, size.x - 1, size.y);
		}
		else {
			SDL_RenderDrawLine(renderer, size.x, 0, 0, size.y);
			SDL_RenderDrawLine(renderer, size.x - 1, 0, 0, size.y - 1);
			SDL_RenderDrawLine(renderer, size.x, 1, 1, size.y);
		}

		//The right coordinate
		double finalX{ static_cast<double>((startPosition.x < endPosition.x ? startPosition.x : endPosition.x) + gv::tileSize / 2) };
		double finalY{ static_cast<double>((startPosition.y < endPosition.y ? startPosition.y : endPosition.y) + gv::tileSize / 2) };
		//The position component
		PositionComponent positionComponent;
		positionComponent.setPosition(ge::Vector2<double>{ finalX, finalY });
		//The renderer component
		RendererComponent rendererComponent;
		rendererComponent.texture = drawer.finishDrawing();
		rendererComponent.positionComponentId = F_FACTORY->positionFactory.addComponent(std::move(positionComponent));
		//The shot renderer component
		ShotRendererComponent shotRendererComponent;
		shotRendererComponent.alpha = 255;
		shotRendererComponent.rendererCompId = F_FACTORY->rendererFactory.addComponent(std::move(rendererComponent));
		SDL_SetTextureBlendMode(F_FACTORY->rendererFactory.getComponent(shotRendererComponent.rendererCompId)->texture.get(), SDL_BLENDMODE_BLEND);
		return F_FACTORY->shotRendererFactory.addComponent(std::move(shotRendererComponent));
	}

	void deleteShot(unsigned int shotRendererId) {
		F_FACTORY->positionFactory.deleteComponent(F_FACTORY->rendererFactory.getComponent(F_FACTORY->shotRendererFactory.getComponent(shotRendererId)->rendererCompId)->positionComponentId);
		F_FACTORY->rendererFactory.deleteComponent(F_FACTORY->shotRendererFactory.getComponent(shotRendererId)->rendererCompId);
		F_FACTORY->shotRendererFactory.deleteComponent(shotRendererId);
	}

	void DamageDealerSystem::update() {
		//For every damage dealer component
		for (auto itd = F_FACTORY->damageDealerFactory.getBeginningIterator(); itd != F_FACTORY->damageDealerFactory.getEndIterator(); itd++) {
			//If this damage dealer can shoot again
			if (ge::Engine::getInstance()->getTimeSinceStart() - itd->lastShotTime > static_cast<long long>(itd->reloadingTime * 1000)) {
				//For every health component
				for (auto ith = F_FACTORY->healthFactory.getBeginningIterator(); ith != F_FACTORY->healthFactory.getEndIterator(); ith++) {
					//If the health is in range of this damage dealer
					if (F_FACTORY->positionFactory.getComponent(itd->positionComponentId)->getPosition().distanceSquared(
						F_FACTORY->positionFactory.getComponent(ith->positionComponentId)->getPosition()) < pow(itd->range, 2)) {
						//Shot it
						ith->health -= itd->damage;
						itd->lastShotTime = ge::Engine::getInstance()->getTimeSinceStart();

						if (F_FACTORY->gameComponent.graphicsOn) {
							//Create the graphic shot
							shotRenderersId.push_back(createShot(F_FACTORY->positionFactory.getComponent(itd->positionComponentId)->getPosition(),
								F_FACTORY->positionFactory.getComponent(ith->positionComponentId)->getPosition()));
						}
						//Escape this for loop to pass to the next damage dealer
						break;
					}
				}
			}
		}

		//Delete the shots
		for (auto it = shotRenderersId.begin(); it != shotRenderersId.end();) {
			if (F_FACTORY->shotRendererFactory.getComponent(*it)->alpha <= 0) {
				deleteShot(*it);
				it = shotRenderersId.erase(it);
			}
			else
				it++;
		}
	}
}
