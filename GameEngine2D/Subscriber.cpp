#include "Subscriber.h"

#include "Publisher.h"

namespace ge {
	void Subscriber::subscribe(Publisher* publisher) {
		publisher->subscribe(this);
		subscribedPublishers.push_back(publisher);
	}

	void Subscriber::unsubscribe(Publisher* publisher) {
		publisher->unsubscribe(this);
		for (auto it = subscribedPublishers.begin(); it != subscribedPublishers.end(); it++) {
			if ((*it) == publisher) {
				subscribedPublishers.erase(it);
				break;
			}
		}
	}

	Subscriber::~Subscriber() {
		while (subscribedPublishers.size() != 0) {
			unsubscribe(subscribedPublishers[0]);
		}
	}
}