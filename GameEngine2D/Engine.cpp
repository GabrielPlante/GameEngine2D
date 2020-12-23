#include "Engine.h"
#include <chrono>
#include <thread>

//Include of the systems
#include "DefaultGraphicSystem.h"
#include "DefaultEventHandler.h"
#include "ScriptSystem.h"
#include "EventSystem.h"

#include "Default2DVertex.h"
#include "CommandList.h"
#include "Input.h"

#ifdef DEBUG_GE
#include <iostream>
#endif

#include "UniformHandler.h"
#include "ShapeCreator.h"
#include "Camera.h"
#include "Batch.h"

constexpr int SCREEN_WIDTH{ 800 };
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
		Input::init(mainWindow);

		addSystem(std::shared_ptr<ge::System>{new ScriptSystem{}});

		//Set the graphic system to the default one
		graphicSystem.reset(new DefaultGraphicSystem{});

		//-----------------Temporary stuff-----------------\\

		std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 o_Color;

uniform vec4 u_CameraTransform;

void main(){
	vec4 position = vec4((a_Position.x + u_CameraTransform.x) * u_CameraTransform.z, (a_Position.y + u_CameraTransform.y) * u_CameraTransform.w, 0.0, 1.0);
	gl_Position = position;

	o_Color = a_Color;
}
)";

		std::string fragmentSrc = R"(
#version 330 core

in vec4 o_Color;
layout(location = 0) out vec4 color;

void main(){
	color = o_Color;
}
)";

		//TEMPORARY KEY BINDING

		std::shared_ptr<Camera> camera{ new Camera{{{0, 0}, static_cast<Vector2<int16_t>>(Vector2<int>{SCREEN_WIDTH, SCREEN_HEIGHT})}, {SCREEN_WIDTH, SCREEN_HEIGHT} } };
		Input::bindKey(glfwGetKeyScancode(GLFW_KEY_O), "camera_up", [=](const std::vector<float>&) {
			camera->move({ 0, 10 });
			}, true);
		Input::bindKey(glfwGetKeyScancode(GLFW_KEY_L), "camera_down", [=](const std::vector<float>&) {
			camera->move({ 0, -10 });
			}, true);
		Input::bindKey(glfwGetKeyScancode(GLFW_KEY_K), "camera_left", [=](const std::vector<float>&) {
			camera->move({ -10, 0 });
			}, true);
		Input::bindKey(39, "camera_right", [=](const std::vector<float>&) {
			camera->move({ 10, 0 });
			}, true);

		Input::bindScroll("camera_scroll", [camera](const std::vector<float>& args) {
			camera->zoom(args[1] * 0.1 + 1);
			});

		std::vector<std::shared_ptr<UniformHandler>> uniHandVec;
		uniHandVec.push_back(std::move(camera));
		Shader shader{ vertexSrc, fragmentSrc, std::move(uniHandVec) };


		//Create the test batch
		std::shared_ptr<HexagonBatch> testBatch{ HexagonBatch::createBatch(Default2DVertex::getAttrib(), std::move(shader), 100) };

		createHexagon(testBatch, { 0, 0 }, 20, { 0.3f, 0.2f, 0.8f, 1.0f });

		//FOR TEST PURPOSE ONLY
		Entity e{ Entity::Create() };
		e.addComponent<std::shared_ptr<HexagonBatch>>(std::move(testBatch));


#ifdef DEBUG_GE
		std::cout << "Debug mode" << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;
#endif
	}

	Engine::~Engine() {
		if (mainWindow)
			delete mainWindow;

		//Delete every entity and every component
		for (auto it = Storage<ComponentHandler>::begin(); it != Storage<ComponentHandler>::end(); it++) {
			it->clear();
		}

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

		ENGINE->quit();
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
