#pragma once
class Entity
{
private:
	//Count what the next entity will have as an id
	static unsigned long idCount;
	//Each entity have a unique id
	const unsigned long id;
public:
	//Default constructor
	Entity();
};

