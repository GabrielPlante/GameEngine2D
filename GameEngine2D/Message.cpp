#include "Message.h"

namespace ge {

	void operator<<(Message& message, float data) {
		message.messageData.push_back(data);
	}

	void operator>>(Message& message, float& data) {
		data = message.messageData.back();
		message.messageData.pop_back();
	}
}