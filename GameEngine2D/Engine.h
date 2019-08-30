#pragma once
#include <vector>
#include <memory>
#include "Clock.h"
#include "System.h"
class Engine
{
private:
	Clock engineClock;
	long long timeSinceStart{ 0 };

	//Time between each frame in milliseconds, with the base being 60 frame per second
	unsigned int timeBetweenFrame{ 1000/60 };

	//Reset the engine clock, but keep track of the time since the engine started, and give how much time passed since the last clock reset
	long long timestep();
	
	//The vector containing all the systems
	std::vector<std::shared_ptr<System>> systems;
public:
	//Default constructor
	Engine(){}

	//Initialise the engine
	void init();

	//The mainLoop, call update each time, and timestep
	void mainLoop();

	//Called each frame
	void update();

	//Add a system to the engine
	void addSystem(std::shared_ptr<System> system) { systems.push_back(system); }
};

