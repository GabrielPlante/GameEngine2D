#pragma once

#include "../GameEngine2D/System.h"

namespace ian {
	class PhysicSystem
		: public ge::System
	{
	private:
	public:
		void update() override;
	};
}
