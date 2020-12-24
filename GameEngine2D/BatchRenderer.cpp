#include "BatchRenderer.h"
#include <GL/glew.h>

#include "Shader.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	void BatchRenderer::renderBatch() const {
		shader->bind();
		shader->bindUniforms();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);

		glDrawElements(GL_TRIANGLES, lastIndexPlace, GL_UNSIGNED_INT, (void*)0);
	}
}
