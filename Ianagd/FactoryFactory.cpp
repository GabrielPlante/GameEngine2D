#include "FactoryFactory.h"

namespace ian {
	unsigned int FactoryFactory::createEntity(const std::vector<int>& componentList) {
		GameEntity entity;
		unsigned int entityId{ entityFactory.addComponent(std::move(entity)) };
		for (int i = 0; i != componentList.size(); i++) {
			entityFactory.getComponent(entityId)->createComponent(componentList[i]);
		}
		return entityId;
	}
}