#include "GraphicSystem.h"

#include "../GameEngine2D/TransformComponent.h"
#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Storage.h"

#include "../GameEngine2D/CircleCreator.h"

#include "MovementComponent.h"

namespace ian {
	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void renderEntities(SDL_Renderer* renderer) {
		for (auto it = ge::Storage<ge::TransformComponent>::begin(); it != ge::Storage<ge::TransformComponent>::end(); it++) {
			//Create the circle
			constexpr int circleRadius{ 16 };
			ge::CircleCreator circleCreator{ circleRadius, { 100, 100, 100 }, true };
			auto circle{ circleCreator.getTexture() };
			//Render the circle, with the center of the circle in the position
			circle.render(renderer, { static_cast<int>(it->position.x - circleRadius), static_cast<int>(it->position.y - circleRadius) });
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
