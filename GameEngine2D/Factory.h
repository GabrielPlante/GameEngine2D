#pragma once
#include <vector>

//Factory is the template class that will hold every component of a component type
template <typename Component>
class Factory
{
private:
	std::vector<Component> componentList;
public:
	//Add a component to the list
	void addComponent(Component component) { componentList.push_back(component); }
};

