#pragma once
#include <SDL.h>

#include "Camera.h"

namespace ge {
	class Renderable
	{
	public:
		//Render the texture
		virtual void render(SDL_Renderer* renderer, const Camera& camera, const Position<>& position) const = 0;
	};

}
