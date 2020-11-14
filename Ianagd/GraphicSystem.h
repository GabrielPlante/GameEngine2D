#pragma once

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Window.h"

namespace ian {
	/// <summary>
	/// The grapic system
	/// </summary>
	/// <seealso cref="ge::System" />
	class GraphicSystem :
		public ge::System
	{
	private:
		ge::Window window;

		ge::TextureWrapper mapTexture;
	public:
		//Constructor
		GraphicSystem(int screenWidth, int screenHeight);

		//Add a map texture to the engine
		void addMapTexture(ge::TextureWrapper newMapTexture) { mapTexture = newMapTexture; }

		//Update the system
		void update() override;

		//Get the renderer from the window
		SDL_Renderer* getWindowRenderer() const { return window.getRenderer(); }
	};
}
