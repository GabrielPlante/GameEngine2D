#pragma once
#include <array>

#include "../GameEngine2D/Entity.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class GameEntity :
		public ge::Entity
	{
	private:
		ge::Vector2<long> position = ge::Vector2<long>{ 0, 0 };

		//The array of every control component
		std::array<unsigned int, 1> controlComponentId;
	public:
		//Set the entity position
		void setPosition(ge::Vector2<long> newPosition) { position = newPosition; }

		//Get the entity position
		ge::Vector2<long> getPosition() { return position; }

		//Move the entity with an offset
		void changePosition(ge::Vector2<long> offset) { position += offset; }

		//Add a control component id to this entity
		void addControlComponentId(int index, unsigned int componentId) { controlComponentId[index] = componentId; }

		//Get the id of a control component associated with this entity
		unsigned int getControlComponentId(int index) const { return controlComponentId[index]; }
	};
}

