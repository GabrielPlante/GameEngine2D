#pragma once
#include "../GameEngine2D/Entity.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class GameEntity :
		public ge::Entity
	{
	private:
		ge::Vector2<long> position = ge::Vector2<long>{ 0, 0 };
	public:
		//Set the entity position
		void setPosition(ge::Vector2<long> newPosition) { position = newPosition; }

		//Get the entity position
		ge::Vector2<long> getPosition() { return position; }

		//Move the entity with an offset
		void changePosition(ge::Vector2<long> offset) { position += offset; }
	};
}

