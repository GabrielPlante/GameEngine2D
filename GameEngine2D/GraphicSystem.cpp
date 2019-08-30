#include "GraphicSystem.h"

GraphicSystem::GraphicSystem(const int screenWidth, const int screenHeight)
	:window{ screenWidth, screenHeight }
{
}

void GraphicSystem::init() {

}

void GraphicSystem::update() {
	window.clear();

	//Every other update goes here

	window.render();
}
