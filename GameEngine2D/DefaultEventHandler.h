#pragma once
#include "EventHandler.h"

namespace ge {
	class DefaultEventHandler : public EventHandler
	{
	public:
		//Constructor
		DefaultEventHandler();

		//Update the event handler
		void update() override;
	};
}
