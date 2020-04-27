#pragma once

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class PositionComponent
	{
	private:
		//The position is internally stored in double to avoid small change not affecting the position
		ge::Vector2<double> position;

	public:
		//Getter to long so it's easier to work with a position
		ge::Vector2<> getPosition() const { return { static_cast<long>(position.x), static_cast<long>(position.y) }; }

		//Get the real position in double
		ge::Vector2<double> getDPosition() const { return position; }

		//Setter
		void setPosition(ge::Vector2<double> newPosition) { position = newPosition; }
		void setPosition(ge::Vector2<> newPosition) { position.x = static_cast<double>(newPosition.x), position.y = static_cast<double>(newPosition.y); }

		//Move the position by an offset
		void movePosition(ge::Vector2<double> offset) { position += offset; }
	};
}
