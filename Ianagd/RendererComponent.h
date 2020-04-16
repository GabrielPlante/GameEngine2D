#pragma once
#include <SDL.h>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class GameEntity;

	class RendererComponent
	{
	public:
		//The position
		unsigned int positionComponentId;

		//The texture rendered
		SDL_Texture* texture;

		//The source rectangle, basically what you take of the texture. Keep to null to take the entire texture
		SDL_Rect* srcRect = nullptr;

		//The size of the texture to render on screen
		ge::Vector2<int> size;
	};

}
