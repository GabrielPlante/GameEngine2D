#pragma once
struct PhysicComponent
{
private:
	const long ownerEntityID;
public:
	//The actual attribute are public because it's not the component that change them, it's the system
	long x{ 0 };
	long y{ 0 };

	//Constructor
	PhysicComponent(const long ownerEntityID)
		:ownerEntityID{ ownerEntityID }
	{}

	//Get the entity ID of the owner of this component
	long getOwnerEntityID() const { return ownerEntityID; }
};

