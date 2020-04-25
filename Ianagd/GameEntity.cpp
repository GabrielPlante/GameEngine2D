#include "GameEntity.h"

#include "../GameEngine2D/Console.h"

#include "FactoryFactory.h"
#include "GameCore.h"

namespace ian {
	GameEntity::GameEntity() {
		//Initialise the components id to 0
		for (int i = 0; i != componentsId.size(); i++) {
			componentsId[i] = 0;
		}
	}
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
		case tileMovementCompId:
		{
			TileMovementComponent tileMovementComponent;
			componentId = F_FACTORY->tileMovementFactory.addComponent(std::move(tileMovementComponent));
			break;
		}
		case healthCompId:
		{
			HealthComponent healthComponent;
			componentId = F_FACTORY->healthFactory.addComponent(std::move(healthComponent));
			break;
		}
		default:
			CONSOLE_LOG_ERROR("GameEntity::CreateComponent error: this type of component doesn't exist or can't be added to an entity")
			return 0;
		}
		componentsId[type] = componentId;
		return componentId;
	}

	GameEntity* GameEntity::deleteComponent(int index) {
		switch (index)
		{
		case positionCompId:
			F_FACTORY->positionFactory.deleteComponent(componentsId[index]);
			componentsId[index] = 0;
			break;
		case rendererCompId:
			F_FACTORY->rendererFactory.deleteComponent(componentsId[index]);
			componentsId[index] = 0;
			break;
		case movementCompId:
			F_FACTORY->movementFactory.deleteComponent(componentsId[index]);
			componentsId[index] = 0;
			break;
		case tileMovementCompId:
			F_FACTORY->tileMovementFactory.deleteComponent(componentsId[index]);
			componentsId[index] = 0;
			break;
		case healthCompId:
			F_FACTORY->healthFactory.deleteComponent(componentsId[index]);
			componentsId[index] = 0;
			break;
		default:
			break;
		}
		return this;
	}

	void GameEntity::deleteAllComponent() {
		for (int i = 0; i != componentsId.size(); i++) {
			if (componentsId[i] != 0)
				deleteComponent(i);
		}
	}

	GameEntity* GameEntity::managePosition(ge::Vector2<> position) {
		F_FACTORY->positionFactory.getComponent(componentsId[positionCompId])->position = position;
		return this;
	}

	GameEntity* GameEntity::manageRenderer(const ge::TextureWrapper& texture, ge::Vector2<int> size, SDL_Rect* srcRect) {
		F_FACTORY->rendererFactory.getComponent(componentsId[rendererCompId])->positionComponentId = componentsId[positionCompId];
		F_FACTORY->rendererFactory.getComponent(componentsId[rendererCompId])->texture = texture;
		F_FACTORY->rendererFactory.getComponent(componentsId[rendererCompId])->size = size;
		F_FACTORY->rendererFactory.getComponent(componentsId[rendererCompId])->srcRect = srcRect;
		return this;
	}

	GameEntity* GameEntity::manageMovement(ge::Vector2<> destination, float speed, bool isMoving) {
		F_FACTORY->movementFactory.getComponent(componentsId[movementCompId])->positionComponentId = componentsId[positionCompId];
		F_FACTORY->movementFactory.getComponent(componentsId[movementCompId])->destination = destination;
		F_FACTORY->movementFactory.getComponent(componentsId[movementCompId])->speed = speed;
		F_FACTORY->movementFactory.getComponent(componentsId[movementCompId])->isMoving = isMoving;
		return this;
	}

	GameEntity* GameEntity::manageTileMovement(std::stack<ge::Vector2<int>> destinationStack, float speed, bool isMoving) {
		F_FACTORY->tileMovementFactory.getComponent(componentsId[tileMovementCompId])->positionComponentId = componentsId[positionCompId];
		F_FACTORY->tileMovementFactory.getComponent(componentsId[tileMovementCompId])->destinationStack = destinationStack;
		F_FACTORY->tileMovementFactory.getComponent(componentsId[tileMovementCompId])->speed = speed;
		F_FACTORY->tileMovementFactory.getComponent(componentsId[tileMovementCompId])->isMoving = isMoving;
		return this;
	}

	GameEntity* GameEntity::manageHealth(int health) {
		F_FACTORY->healthFactory.getComponent(componentsId[healthCompId])->positionComponentId = componentsId[positionCompId];
		F_FACTORY->healthFactory.getComponent(componentsId[healthCompId])->health = health;
		return this;
	}
}
