#pragma once
#include <vector>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class TowerManager
	{
	private:
		std::vector<unsigned int> towersId;
	public:
		//Build a tower. Return true if the tower has been build, false otherwise
		bool buildTower(ge::Vector2<> position, int type);

		//Clear the tower
		void clear() { towersId.clear(); }
	};
}

