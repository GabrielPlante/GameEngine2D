#include "Subscriber.h"

#include "Publisher.h"

namespace ge {

	void Subscriber::proccessMessages() {
		while (!pendingMessages.empty()) {
			handleMessage(pendingMessages.back());
			pendingMessages.pop_back();
		}
	}

	void Subscriber::subscribeTo(Publisher* publisher) {
		publisher->subscribe(this);
		subscribedPublishers.push_back(publisher);
	}

	void Subscriber::unsubscribe(Publisher* publisher) {
		//Notify the publisher that we unsubscribe from him
		publisher->unsubscribe(this);
		//Delete it from the list of our publisher
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