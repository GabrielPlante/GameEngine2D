#include "Engine.h"
#include <chrono>
#include <thread>

#include "GraphicSystem.h"

#include <iostream>

//Size of the screen
constexpr int SCREEN_WIDTH{ 1200 };
constexpr int SCREEN_HEIGHT{ 600 };

long long Engine::timestep() {
	long long timeSinceLastReset = engineClock.resetTime();
	timeSinceStart += timeSinceLastReset;
	return timeSinceLastReset;
}

Engine::Engine() {
	//Adding the graphic system
	addSystem(std::shared_ptr<System>{new GraphicSystem{ SCREEN_WIDTH, SCREEN_HEIGHT }});
}

void Engine::mainLoop() {
	while (true) {
		long long timeSinceLastReset = timestep();

		//Call the engine update
		update();


		//---TEST---
		std::cout << "Time since last reset : " << timeSinceLastReset/1000 << std::endl << "Time since start : " << timeSinceStart/1000 << std::endl;

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
}
