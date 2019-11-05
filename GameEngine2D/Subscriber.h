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
		std::vector<Publisher*> subscribedPublishers;
	public:
		//Handle a message a publisher will give to it's subscriber
		virtual void handleMessage(std::shared_ptr<Message> message) = 0;

		//Subscribe to a publisher
		void subscribe(Publisher* publisher);

		//Unsubscribe to a publisher
		void unsubscribe(Publisher* publisher);

		//The base class destructor unsubscribe from every publisher in the subscribed list
		~Subscriber();
	};
}
