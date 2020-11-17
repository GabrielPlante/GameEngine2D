#include "GraphicSystem.h"

namespace ge {
	GraphicSystem::GraphicSystem(const int screenWidth, const int screenHeight)
		:window{ screenWidth, screenHeight }
	{
	}

	void GraphicSystem::update() {
		window.clear();

		//Every other update goes here

		window.render();
	}
}
