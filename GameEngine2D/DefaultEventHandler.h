#pragma once
#include "EventHandler.h"

namespace ge {
	class DefaultEventHandler : public EventHandler
	{
		//Update the event handler
		void update() override;
	};
}