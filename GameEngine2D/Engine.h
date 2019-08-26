#pragma once
#include "Clock.h"
class Engine
{
private:
	Clock engineClock;
	long long timeSinceStart{ 0 };

	//Reset the engine clock, but keep track of the time since the engine started
	long long timestep();
public:
	//Default constructor
	Engine();

	//Initialise the engine
	void init();

	//Called each frame
	void update();
};

