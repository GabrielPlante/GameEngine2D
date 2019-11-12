#include "ComponentHandle.h"

#include "Engine.h"

namespace ge {

	void ComponentHandle::sendMessage(std::shared_ptr<Message> message) const {
		(*message) << static_cast<float>(componentId);
		associatedSystem->handleMessage(message);
	}

}