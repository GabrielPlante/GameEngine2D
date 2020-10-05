#pragma once

#include "TextureWrapper.h"
#include "Color.h"

namespace ge {
	/* A texture creator is a base class for classes that create a texture, for example a circle or a rectangle
	*/
	class TextureCreator
	{
	protected:
		TextureWrapper texture;
	public:
		//Get the texture of the circle
		TextureWrapper getTexture() const { return texture; }
	};
}

