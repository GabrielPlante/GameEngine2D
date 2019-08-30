#pragma once
#include "System.h"
#include "Window.h"
/*
 * GraphicSystem is the system that manage everything appearing on screen.
*/
class GraphicSystem
	: public System
{
private:
	Window window;
public:
	//Constructor
	GraphicSystem(const int screenWidth, const int screenHeight);

	//Initialisation
	void init() override;

	//What will update all component under this system control
	void update() override;
};

