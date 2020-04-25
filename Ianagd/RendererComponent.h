#pragma once
#include <SDL.h>

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class RendererComponent
	{
	public:
		//The texture
		ge::TextureWrapper texture;

		//The position
		unsigned int positionComponentId;

		//The source rectangle, basically what you take of the texture. Keep to null to take the entire texture
		SDL_Rect* srcRect{ nullptr };

		//The size of the texture to render on screen
		ge::Vector2<int> size;
	};
}
