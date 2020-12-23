#pragma once

namespace ge {
	//Struct regrouping what OpenGL need to know about one attribute of a vertex
	//An attribute is basically what a part of a vertex is,
	//For example, a position is two float at the start of the vertex
	struct VertexAttrib {
		int size; //In component
		uint32_t type;
		unsigned char normalized{ 0 };
		const void* pointer;
	};
}
