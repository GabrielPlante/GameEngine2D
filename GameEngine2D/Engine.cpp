#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "DefaultEventHandler.h"
#include "ScriptSystem.h"
#include "EventSystem.h"

#include "CommandList.h"

#include "Entity.h"

namespace ge {
	//Initialize static attribute
	Engine* Engine::instance{ nullptr };

	long long Engine::timestep() {
		long long timeSinceLastReset = engineClock.resetTime();
		timeSinceStart += timeSinceLastReset;
		return timeSinceLastReset;
	}

	//In the constructor many systems are added to the engine, the order in wich they are added will be their order of calling, so it matter
	Engine::Engine()
	{
		std::unique_ptr<EventHandler> defaultEventSystem{ std::unique_ptr<EventHandler>{new DefaultEventHandler{}} };
		pushEventHandler(std::move(defaultEventSystem));

		//Initialise the command list
		CommandList::init();

		addSystem(std::shared_ptr<ge::System>{new ScriptSystem{}});

	}

	Engine::~Engine() {
		//Delete every entity and every component
		Storage<ComponentHandler>::clear();

		//Quit the command list
		CommandList::quit();
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

			//If less time past since the last frame than what the engine want, it sleep to compensate for it
			if (engineClock.getTime() < static_cast<long long>(timeBetweenFrame) * 1000) {
				std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(timeBetweenFrame) * 1000 - engineClock.getTime()));
			}
		}

		//Quit properly the engine
		Engine::quit();
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
