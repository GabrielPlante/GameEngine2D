#pragma once

#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Window.h"
#include "../GameEngine2D/Factory.h"

#include "RendererComponent.h"

namespace ian {

	/// <summary>
	/// The grapic system of the game
	/// </summary>
	/// <seealso cref="ge::System" />
	class GameGraphicSystem :
		public ge::System
	{
	private:
		ge::Window window;

		ge::Factory<RendererComponent>* rendererComponentFactory;
	public:
		//Constructor
		GameGraphicSystem(int screenWidth, int screenHeight, ge::Factory<RendererComponent>* rendererComponentFactory);

		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};

		//Get the renderer from the window
		SDL_Renderer* getWindowRenderer() const { return window.getRenderer(); }
	};
}

