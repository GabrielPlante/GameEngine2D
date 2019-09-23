#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "EventSystem.h"
#include "GraphicSystem.h"
#include "MovementSystem.h"

#include <iostream>

//Initialize static attribute
Engine* Engine::instance{ nullptr };

//Size of the screen
constexpr int SCREEN_WIDTH{ 1200 };
constexpr int SCREEN_HEIGHT{ 600 };

long long Engine::timestep() {
	long long timeSinceLastReset = engineClock.resetTime();
	timeSinceStart += timeSinceLastReset;
	return timeSinceLastReset;
}

//In the constructor many systems are added to the engine, the order in wich they are added will be their order of calling, so it matter
Engine::Engine()
{
	//Adding the event system, first do it's updated first so the order arrive first
	addSystem(std::shared_ptr<System>{new EventSystem{}});

	//-----Every system need to be added AFTER this line-----

	addSystem(std::shared_ptr<System>{new MovementSystem{}});

	//-----Every system need to be added BEFORE this line-----

	//Add the graphic system to his dedicated variable
	graphicSystem = std::shared_ptr<GraphicSystem>{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
}

void Engine::init() {
	if (!instance) {
		instance = new Engine{};
	}
}

void Engine::quit() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void Engine::mainLoop() {
	while (keepRunning) {
		timeSinceLastFrame = timestep();

		//Call the engine update
		update();


		//---TEST---Print the time since last reset and the time since start
		//std::cout << "Time since last reset : " << timeSinceLastReset/1000 << std::endl << "Time since start : " << timeSinceStart/1000 << std::endl;

		//If less time past since the last frame than what the engine want, it sleep to compensate for it
		if (engineClock.getTime() < static_cast<long long>(timeBetweenFrame) * 1000) {
			std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(timeBetweenFrame) * 1000 - engineClock.getTime()));
		}
	}
}

void Engine::update() {
	//Each update, the engine update each system
	for (std::shared_ptr<System> system : systems) {
		system->update();
	}

	//At the end, the graphic system is updated
	graphicSystem->update();
}
