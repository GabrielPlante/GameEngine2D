#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "DefaultGraphicSystem.h"
#include "DefaultEventHandler.h"
#include "ScriptSystem.h"
#include "EventSystem.h"

#include "CommandList.h"

#include "Entity.h"

#ifdef DEBUG_GE
#include <iostream>
#endif

#include "Batch.h"

constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace ge {
	//Initialize static attribute
	Engine* Engine::instance{ nullptr };

	long long Engine::timestep() {
		timeSinceLastFrame = engineClock.resetTime();
		timeSinceStart += timeSinceLastFrame;
		return timeSinceLastFrame;
	}

	//In the constructor many systems are added to the engine, the order in wich they are added will be their order of calling, so it matter
	Engine::Engine()
	{
		//First, initialise the window
		mainWindow = new Window{ SCREEN_WIDTH, SCREEN_HEIGHT };

		std::unique_ptr<EventHandler> defaultEventSystem{ std::unique_ptr<EventHandler>{new DefaultEventHandler{}} };
		pushEventHandler(std::move(defaultEventSystem));

		CommandList::init();

		addSystem(std::shared_ptr<ge::System>{new ScriptSystem{}});

		std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

void main(){
	gl_Position = vec4(a_Position, 1.0);
}
)";

		std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

void main(){
	color = vec4(0.8, 0.2, 0.3, 1.0);
}
)";

		Shader shader{ vertexSrc, fragmentSrc };
		//Set the graphic system to the default one
		graphicSystem.reset(new DefaultGraphicSystem{ std::move(shader) });


		//Create the test batch
		std::unique_ptr<Batch<ge::Vector2<float>, 1, 4, 6>> testBatch{ Batch<ge::Vector2<float>, 1, 4, 6>::createBatch({{2, GL_FLOAT, GL_FALSE, (const void*)0}}) };
		constexpr int size{ 4 };
        std::array<Vector2<float>, size> position{
            Vector2<float>{0.0f, -0.5f},
            Vector2<float>{0.0f,  0.5f},
            Vector2<float>{0.5f, -0.5f},
            Vector2<float>{0.5f,  0.5f}
        };

        constexpr int iSize{ 6 };
        std::array<uint32_t, iSize> indexes{
            0, 1, 2,
            1, 2, 3
        };
		testBatch->addObject(position, indexes);
		//FOR TEST PURPOSE ONLY
		testBatch.release();


#ifdef DEBUG_GE
		std::cout << "Debug mode" << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;
#endif
	}

	Engine::~Engine() {
		if (mainWindow)
			delete mainWindow;

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
			//Calculate the time since the last frame
			timestep();

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
