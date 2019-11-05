#pragma once
#include <vector>
#include <memory>

namespace ge {
	class Subscriber;
	class Message;
	 /// <summary>
	 /// A publisher host subscribers and notify them when he have a message
	 /// </summary>
	class Publisher
	{
	private:
		std::vector<Subscriber*> subscribers;
	public:
		//Subscribe to this publisher, to get notified of all the message he have. Does not check if you are already subscribed
		void subscribe(Subscriber* subscriber) { subscribers.push_back(subscriber); }

		//Unsubscribe to this publisher
		void unsubscribe(Subscriber* subscriber);

		//Notify all the subscribers of the message we have
		void notify(std::shared_ptr<Message> message) const;
	};
}
