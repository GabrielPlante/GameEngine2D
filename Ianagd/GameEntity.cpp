#include "GameEntity.h"

#include "../GameEngine2D/Console.h"

#include "GameCore.h"

namespace ian {
	unsigned int GameEntity::createComponent(int type) {
		unsigned int componentId{ 0 };
		switch (type)
		{
		case 0:
		{
			PositionComponent positionComponent;
			componentId = F_FACTORY->positionFactory.addComponent(std::move(positionComponent));
			break;
		}
		case 1:
		{
			RendererComponent rendererComponent;
			componentId = F_FACTORY->rendererFactory.addComponent(std::move(rendererComponent));
			break;
		}
		case 2:
		{
			MovementComponent movementComponent;
			componentId = F_FACTORY->movementFactory.addComponent(std::move(movementComponent));
			break;
		}
		case 3:
		{
			CollisionComponent collisionComponent;
			componentId = F_FACTORY->collisionFactory.addComponent(std::move(collisionComponent));
			break;
		}
		default:
			CONSOLE_LOG_ERROR("GameEntity::CreateComponent error: this type of component doesn't exist")
			return 0;
		}
		componentsId[type] = componentId;
		return componentId;
	}
}
