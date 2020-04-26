#pragma once

#include "../GameEngine2D/TextureWrapper.h"

namespace ian {
	class UIComponent
	{
	public:
		//Get the size of the texture
		ge::Vector2<int> getSize() const {
			int w, h;
			SDL_QueryTexture(texture.get(), NULL, NULL, &w, &h);
			return { w, h };
		}

		unsigned int positionComponentId;

		ge::TextureWrapper texture;
	};
}
