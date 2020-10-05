#pragma once
#include "TextureCreator.h"

namespace ge {
	class CircleCreator
		: public TextureCreator
	{
	public:
		//Constructor
		CircleCreator(int32_t radius, Color color, bool disk = false, bool blend = true);
	};
}

