#pragma once

namespace ge {
	class Component;

	class System
	{
	public:
		//What will update all component under this system control
		virtual void update() = 0;
	};

}
