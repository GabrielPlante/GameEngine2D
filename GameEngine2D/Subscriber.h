#pragma once
#include <memory>
#include <vector>

#include "Message.h"

namespace ge{
	class Publisher;	
	/// <summary>
	/// A subscriber can subscribe to a publisher to get notified when he have a message
	/// </summary>
	class Subscriber
	{
	private:
		//Every publisher this subscribed to
		std::vector<Publisher*> subscribedPublishers;

		//The list of message needed to be proccessed
		std::vector<std::shared_ptr<Message>> pendingMessages;
	public:
		//Handle a message a publisher will give to it's subscriber
		virtual void handleMessage(std::shared_ptr<Message> message) = 0;

		//Send a message to this subsciber
		void receiveMessage(std::shared_ptr<Message> message) { pendingMessages.push_back(message); }

		//Proccess every pending message
		void proccessMessages();

		//Subscribe to a publisher, and add itself to the publisher subscriber list
		void subscribeTo(Publisher* publisher);

		//Unsubscribe to a publisher
		void unsubscribe(Publisher* publisher);

		//The base class destructor unsubscribe from every publisher in the subscribed list
		~Subscriber();
	};
}
