#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "EventSystem.h"

#include "Console.h"

#include "CommandList.h"

namespace ge {
	//Initialize static attribute
	Engine* Engine::instance{ nullptr };

	long long Engine::timestep() {
		long long timeSinceLastReset = engineClock.resetTime();
		timeSinceStart += timeSinceLastReset;
		return timeSinceLastReset;
	}

	//In the constructor many systems are added to the engine, the order in wich they are added will be their order of calling, so it matter
	Engine::Engine(int screenWidth, int screenHeight)
	{
		//First initialise the graphic system, that initialise sdl and sdl_ttf
		//graphicSystem = std::shared_ptr<GraphicSystem>{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };

		//Then initialise the console
		Console::init(Rectangle{ 100, 100, screenWidth * 2 / 3, screenHeight * 2 / 3 });

		//Initialise the command list
		CommandList::init();

		CONSOLE_LOG("Engine successfully initialised");

	}

	Engine::~Engine() {
		CONSOLE_LOG("Engine shutting down");

		//Quit the console
		Console::quit();

		//Quit the command list
		CommandList::quit();
	}

	void Engine::init(int screenWidth, int screenHeight) {
		if (!instance) {
			instance = new Engine{ screenWidth, screenHeight };
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

			//If less time past since the last frame than what the engine want, it sleep to compensate for it
			if (engineClock.getTime() < static_cast<long long>(timeBetweenFrame) * 1000) {
				std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(timeBetweenFrame) * 1000 - engineClock.getTime()));
			}
		}
	}

	void Engine::update() {
		//Update the event system
		eventSystem.update();

		//Each update, the engine update each system
		for (std::shared_ptr<System> system : systems) {
			system->update();
		}

		//At the end, the graphic system is updated
		graphicSystem->update();
	}
}
