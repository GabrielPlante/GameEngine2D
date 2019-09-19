#pragma once
#include "System.h"
#include "Factory.h"
#include "MovementComponent.h"

class MovementSystem :
	public System
{
private:
	Factory<MovementComponent> movementComponentFactory;
public:
	//Update all the component in the factory, making them move and rotate effectively
	void update() override;
};

