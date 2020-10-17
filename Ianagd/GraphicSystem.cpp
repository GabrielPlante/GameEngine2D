#include "GraphicSystem.h"

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Storage.h"

#include "../GameEngine2D/CircleCreator.h"

#include "MovementComponent.h"

namespace ian {
	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void renderEntities(SDL_Renderer* renderer) {
		for (auto it = ge::Storage<MovementComponent>::begin(); it != ge::Storage<MovementComponent>::end(); it++) {
			ge::CircleCreator circleCreator{ 15, { 100, 100, 100 }, true };
			auto circle{ circleCreator.getTexture() };
			circle.render(renderer, { static_cast<int>(it->position.x), static_cast<int>(it->position.y) });
		}
	}

	void GraphicSystem::update() {

		//Update the console
		ge::Console::getInstance()->update(getWindowRenderer());

		//Clear the window
		window.clear();

		//Render the map texture
		mapTexture.render(window.getRenderer());

		//Render the entities
		renderEntities(window.getRenderer());

		//Render the console
		ge::Console::getInstance()->render(getWindowRenderer());

		//Render the window
		window.render();
	}
}
