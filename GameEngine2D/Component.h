#pragma once
class Component
{
private:
	const long ownerEntityID;
public:
	//Constructor
	Component(const long ownerEntityID)
		:ownerEntityID{ ownerEntityID }
	{}

	//Get the entity ID of the owner of this component
	long getOwnerEntityID() const { return ownerEntityID; }
};

