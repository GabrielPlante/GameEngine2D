#pragma once
#include "Subscriber.h"

namespace ge {

	/// <summary>
	/// A system handle a part of the game, often with component
	/// <para> Update is the only method that need to be override in a derived class.</para>
	/// </summary>
	class System
	{
	public:
		//What will update all component under this system control
		virtual void update() = 0;
	};
}
