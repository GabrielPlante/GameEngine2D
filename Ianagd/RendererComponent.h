#pragma once
#include <SDL.h>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class RendererComponent
	{
	private:
		//The texture rendered, private for RAII
		SDL_Texture* texture{ nullptr };

		//Destroy the current texture
		void destroyTexture() {
			if (texture != nullptr)
				SDL_DestroyTexture(texture);
		}
	public:
		//Get the texture
		SDL_Texture* getTexture() const { return texture; }

		//Set a new texture. Will delete the previous one if it exist
		void setTexture(SDL_Texture* newTexture) {
			destroyTexture();
			texture = newTexture;
		}

		//Set a new texture without deleting the previous one
		void setTextureWithoutDelete(SDL_Texture* newTexture) {
			texture = newTexture;
		}

		//The position
		unsigned int positionComponentId;

		//The source rectangle, basically what you take of the texture. Keep to null to take the entire texture
		SDL_Rect* srcRect{ nullptr };

		//The size of the texture to render on screen
		ge::Vector2<int> size;
	};
}
