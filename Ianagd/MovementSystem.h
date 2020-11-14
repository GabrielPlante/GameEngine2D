#pragma once
#include "..\GameEngine2D\System.h"

namespace ian {
	class MovementSystem :
		public ge::System
	{
	public:
		//What will update all component under this system control
		void update() override;
	};
}
