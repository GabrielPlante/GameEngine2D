#pragma once
#include "Publisher.h"

namespace ge {

	/// <summary>
	/// A system handle a part of the game, often with component. It's a publisher meaning a subscriber can subscribe to him.	
	/// <para> Update is the only method that need to be override in a derived class.</para>
	/// </summary>
	/// <seealso cref="Publisher" />
	class System
		:public Publisher
	{
	public:
		//What will update all component under this system control
		virtual void update() = 0;
	};
}
