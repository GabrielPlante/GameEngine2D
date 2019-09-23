#pragma once
#include <vector>
#include <memory>

#include "Clock.h"
#include "System.h"

class GraphicSystem;

/*
 * Engine class, singleton
*/
class Engine
{
private:
	Clock engineClock;
	long long timeSinceStart{ 0 };
	//Updated at the very begining of each frame, give the time since the begining of the last frame
	long long timeSinceLastFrame{ 0 };

	static Engine* instance;

	//Boolean that dictate if the main loop continue or stop
	bool keepRunning{ true };

	//Time between each frame in milliseconds, with the base being 60 frame per second
	unsigned int timeBetweenFrame{ 1000/60 };

	//The vector containing all the systems
	std::vector<std::shared_ptr<System>> systems;

	//The graphic system have it's own variable to make sure it is updated last
	std::shared_ptr<GraphicSystem> graphicSystem;

	//Default constructor, private to make it a singleton
	Engine();

	//Reset the engine clock, but keep track of the time since the engine started, and give how much time passed since the last clock reset
	long long timestep();

public:
	//Initialize the engine
	static void init();

	//Return a pointer to the engine instance, or nullptr if it's not initialized yet
	static Engine* getInstance() { return instance; }

	//Quit the engine, destroying this instance
	static void quit();

	//The mainLoop, call update each time, and timestep
	void mainLoop();

	//Called each frame
	void update();

	//Add a system to the engine
	void addSystem(std::shared_ptr<System> system) { systems.push_back(system); }

	//Stop the main loop, stopping the engine
	void stop() { keepRunning = false; }

	//Updated at the very begining of each frame, give the time since the begining of the last frame
	long long getTimeSinceLastFrame() const { return timeSinceLastFrame; }
};

