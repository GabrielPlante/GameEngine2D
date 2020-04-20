#pragma once
#include <array>

namespace ian {

	constexpr int positionCompId{ 0 };
	constexpr int rendererCompId{ 1 };
	constexpr int movementCompId{ 2 };
	constexpr int collisionCompId{ 3 };
	constexpr int tileMovementCompId{ 4 };

	class GameEntity
	{
	private:
		/* The array of every component
		 * 0 : Position component
		 * 1 : Renderer component
		 * 2 : Movement component
		 * 3 : Collision component
		 * 4 : Tile movement component
		 */
		std::array<unsigned int, 5> componentsId;
	public:
		//Add a component id to this entity, return the id of the component in his factory
		unsigned int createComponent(int type);

		//Get the id of a control component associated with this entity
		unsigned int getComponentId(int index) const { return componentsId[index]; }

		void deleteComponent(int index);
	};
}

