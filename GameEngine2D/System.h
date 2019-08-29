#pragma once
class System
{
public:
	//Initialisation
	virtual void init() = 0;

	//What will update all component under this system control
	virtual void update() = 0;
};

