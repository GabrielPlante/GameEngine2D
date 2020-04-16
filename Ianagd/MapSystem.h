#pragma once

#include "../GameEngine2D/System.h"

#include "GameCore.h"

namespace ian {
	///The map system handle generating and rendering the map
	class MapSystem
		: public ge::System
	{
	private:
		ge::Rectangle previousCameraRectangle;

		//The id to the texture of the map
		unsigned int mapRendererId;

		//Render the map on the texture
		void renderMap();
	public:
		//Constructor
		MapSystem(unsigned int mapRendererId) : mapRendererId{ mapRendererId } {}

		//Update the map
		void update() override;

		//Handle the message as a subscriber
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}

