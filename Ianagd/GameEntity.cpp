#include "GameEntity.h"

#include "../GameEngine2D/Console.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {
	unsigned int GameEntity::createComponent(int type) {
		unsigned int componentId{ 0 };
		switch (type)
		{
		case positionCompId:
		{
			PositionComponent positionComponent;
			componentId = F_FACTORY->positionFactory.addComponent(std::move(positionComponent));
			break;
		}
		case rendererCompId:
		{
			RendererComponent rendererComponent;
			componentId = F_FACTORY->rendererFactory.addComponent(std::move(rendererComponent));
			break;
		}
		case movementCompId:
		{
			MovementComponent movementComponent;
			componentId = F_FACTORY->movementFactory.addComponent(std::move(movementComponent));
			break;
		}
		case collisionCompId:
		{
			CollisionComponent collisionComponent;
			componentId = F_FACTORY->collisionFactory.addComponent(std::move(collisionComponent));
			break;
		}
		case tileMovementCompId:
		{
			TileMovementComponent tileMovementComponent;
			componentId = F_FACTORY->tileMovementFactory.addComponent(std::move(tileMovementComponent));
			break;
		}
		default:
			CONSOLE_LOG_ERROR("GameEntity::CreateComponent error: this type of component doesn't exist or can't be added to an entity")
			return 0;
		}
		componentsId[type] = componentId;
		return componentId;
	}

	void GameEntity::deleteComponent(int index) {
		switch (index)
		{
		case positionCompId:
			F_FACTORY->positionFactory.deleteComponent(index);
			break;
		case rendererCompId:
			F_FACTORY->rendererFactory.getComponent(componentsId[index])->setTexture(nullptr);
			F_FACTORY->rendererFactory.deleteComponent(index);
			break;
		case movementCompId:
			F_FACTORY->movementFactory.deleteComponent(index);
			break;
		case collisionCompId:
			F_FACTORY->collisionFactory.deleteComponent(index);
			break;
		case tileMovementCompId:
			F_FACTORY->tileMovementFactory.deleteComponent(index);
			break;
		default:
			break;
		}
	}
}
