#pragma once
#include "IDGenerator.h"

/*
 * A message is a way to communicate over all the enginge and the game.
 * It can be derived to hold additional data.
*/
class Message
{
private:
	//What the message is about
	unsigned int messageType;

	//Where the message come from
	unsigned int messageOrigin;

	//Used to give a unused message type ID to a new message
	static IDGenerator<unsigned int> messageTypeGenerator;
public:
	//Constructor
	Message(unsigned int messageType, unsigned int messageOrigin)
		:messageType{ messageType }, messageOrigin{ messageOrigin }
	{}

	//Get the message type
	unsigned int getMessageType() const { return messageType; }

	//Get the message origin
	unsigned int getMessageOrigin() const { return messageOrigin; }

	//Give a new unused message type I
	static unsigned int getNewMessageType() { return messageTypeGenerator.getNewID(); }
};
