#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "EventSystem.h"

#include "Console.h"

#include "CommandList.h"

#include <iostream>

//Initialize static attribute
Engine* Engine::instance{ nullptr };

long long Engine::timestep() {
	long long timeSinceLastReset = engineClock.resetTime();
	timeSinceStart += timeSinceLastReset;
	return timeSinceLastReset;
}

//In the constructor many systems are added to the engine, the order in wich they are added will be their order of calling, so it matter
Engine::Engine(int screenWidth, int screenHeight, std::unique_ptr<EventHandler> eventHandler)
{
	//First initialise the graphic system, that initialise sdl and sdl_ttf
	//graphicSystem = std::shared_ptr<GraphicSystem>{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };

	//Then initialise the console
	Console::init(Rectangle{ 100, 100, screenWidth * 2 / 3, screenHeight * 2 / 3 });

	//Initialise the command list
	CommandList::init();

	//Initialise the event system, added first into the list so it is updated first
	std::shared_ptr<EventSystem> eventSystem{ new EventSystem };
	//If the user gave another event handler, use it
	if (eventHandler)
		eventSystem->switchEventHandler(std::move(eventHandler));
	addSystem(std::shared_ptr<System>{eventSystem});

	CONSOLE_LOG("Engine successfully initialised");
}

void Engine::init(int screenWidth, int screenHeight, std::unique_ptr<EventHandler> eventHandler) {
	if (!instance) {
		instance = new Engine{screenWidth, screenHeight, std::move(eventHandler)};
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
