#pragma once
#include <vector>

#include "VertexAttrib.h"
#include "Vector2.h"
#include "Color.h"

namespace ge {
	//Represent a standard 2D vertex
	struct Default2DVertex {
		Vector2<float> position;

		Color color;

		//Get the vertex attributes of the class
		static std::vector<VertexAttrib> getAttrib();
	};
}
