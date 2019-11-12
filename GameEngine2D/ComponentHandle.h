#pragma once
#include <memory>

namespace ge {
	class Message;
	class System;

	class ComponentHandle
	{
	private:
		unsigned int componentId;

		System* associatedSystem;

	public:
		//Constructor
		ComponentHandle(unsigned int componentId, System* associatedSystem)
			: componentId{ componentId }, associatedSystem{ associatedSystem }
		{}

		//Send a message to this component
		void sendMessage(std::shared_ptr<Message> message) const;

	};
}
