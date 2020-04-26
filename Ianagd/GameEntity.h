#pragma once
#include <array>
#include <stack>

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Vector2.h"

struct SDL_Texture;
struct SDL_Rect;

namespace ian {

	constexpr int positionCompId{ 0 };
	constexpr int rendererCompId{ 1 };
	constexpr int movementCompId{ 2 };
	constexpr int tileMovementCompId{ 3 };
	constexpr int healthCompId{ 4 };
	constexpr int damageDealerCompId{ 5 };

	class GameEntity
	{
	private:
		/* The array of every component
		 * 0 : Position component
		 * 1 : Renderer component
		 * 2 : Movement component
		 * 3 : Tile movement component
		 * 4 : Health component
		 * 5 : Damage dealer component
		 */
		std::array<unsigned int, 6> componentsId;
	public:
		//Default constructor
		GameEntity();

		//Add a component id to this entity, return the id of the component in his factory
		unsigned int createComponent(int type);

		//Get the id of a control component associated with this entity
		unsigned int getComponentId(int index) const { return componentsId[index]; }

		//Delete a component of the entity
		GameEntity* deleteComponent(int index);

		//Delete every component this entity has
		void deleteAllComponent();

		//Component manager
		GameEntity* managePosition(ge::Vector2<> position);
		GameEntity* manageRenderer(const ge::TextureWrapper& texture, SDL_Rect* srcRect = nullptr);
		GameEntity* manageMovement(ge::Vector2<> destination = { 0, 0 }, float speed = 1, bool isMoving = false);
		GameEntity* manageTileMovement(std::stack<ge::Vector2<int>> destination = {}, float speed = 1, bool isMoving = false);
		GameEntity* manageHealth(int health);
		GameEntity* manageDamageDealer(int damage, int range, int reloadingTime);
	};
}

