#include "Default2DVertex.h"
#include <GL/glew.h>

namespace ge {
	std::vector<VertexAttrib> Default2DVertex::getAttrib()
	{
		std::vector<VertexAttrib> attribs;
		attribs.push_back({ 2, GL_FLOAT, GL_FALSE, (const void*)offsetof(Default2DVertex, position) });
		attribs.push_back({ 4, GL_FLOAT, GL_FALSE, (const void*)offsetof(Default2DVertex, color) });
		return attribs;
	}
}