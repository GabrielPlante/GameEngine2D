#include "Publisher.h"

#include "Subscriber.h"

namespace ge {
	void Publisher::unsubscribe(Subscriber* subscriber) {
		for (auto it = subscribers.begin(); it != subscribers.end(); it++) {
			if ((*it) == subscriber) {
				subscribers.erase(it);
				break;
			}
		}
	}

	void Publisher::publish(std::shared_ptr<Message> message) const {
		for (auto it = subscribers.begin(); it != subscribers.end(); it++) {
			(**it).sendMessage(message);
		}
	}
}