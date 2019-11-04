#pragma once
#include "Publisher.h"

namespace ge {

	//A system handle a part of the game, often with component. It's a publisher meaning a subscriber can subscribe to him.
	class System
		:public Publisher
	{
	public:
		//What will update all component under this system control
		virtual void update() = 0;
	};

}
