#include "GameSystem.h"

#include "../GameEngine2D/TextInRect.h"
#include "../GameEngine2D/Rectangle.h"
#include "../GameEngine2D/Drawer.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {
	void GameSystem::renderGold(int amount) {
		//Create a text
		ge::Rectangle textRect{ 730, 0, 200, 50 };
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({ textRect.w, textRect.h }, { 100, 100, 100, 150 }) };
		ge::TextInRect text{ { 0, 0, 0, 0 }, std::to_string(amount), renderer, { 0, 0 }, ge::Font{ textRect.h }, { 255, 215, 0 } };
		text.render(renderer);

		if (goldRendererId == 0) {
			UIComponent textComponent;
			textComponent.texture = drawer.finishDrawing(true);
			PositionComponent textPos;
			textPos.setPosition(ge::Vector2<>{ textRect.x, textRect.y });
			textComponent.positionComponentId = F_FACTORY->positionFactory.addComponent(std::move(textPos));
			goldRendererId = F_FACTORY->uiFactory.addComponent(std::move(textComponent));
		}
		else {
			F_FACTORY->uiFactory.getComponent(goldRendererId)->texture = drawer.finishDrawing(true);
		}
	}

	void GameSystem::update() {
		if (previousGold != F_FACTORY->gameComponent.playerGold) {
			previousGold = F_FACTORY->gameComponent.playerGold;
			renderGold(previousGold);
		}
	}

}
