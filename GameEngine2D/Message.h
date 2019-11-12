#pragma once
#include <vector>

namespace ge {
	/// <summary>
	/// A message is a way to communicate over all the enginge and the game.
	/// <para>It may be derived to hold additional data.</para>
	/// </summary>
	class Message
	{
	private:
		//What the message is about
		unsigned int messageType;

		//Where the message come from
		unsigned int messageOrigin;

	public:
		//The message data
		std::vector<float> messageData;

		//Constructor
		Message(unsigned int messageType, unsigned int messageOrigin, const std::vector<float>& messageData = std::vector<float>{})
			:messageType{ messageType }, messageOrigin{ messageOrigin }, messageData{ messageData }
		{}

		//Get the message type
		unsigned int getMessageType() const { return messageType; }

		//Get the message origin
		unsigned int getMessageOrigin() const { return messageOrigin; }

	};

	//Operator override to put float data inside a message
	void operator<<(Message& message, float data);

	//Operator override to extract float data from a message
	void operator>>(Message& message, float& data);
}
