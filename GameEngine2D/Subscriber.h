#pragma once
#include <memory>

#include "Message.h"

/*
 * A subscriber can subscribe to a publisher to get notified when he have a message
*/
class Subscriber
{
public:
	virtual void handleMessage(std::shared_ptr<Message> message) = 0;
};
