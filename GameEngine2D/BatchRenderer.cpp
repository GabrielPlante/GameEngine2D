#include "BatchRenderer.h"
#include <GL/glew.h>

namespace ge {
	void BatchRenderer::renderBatch() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);

		glDrawElements(GL_TRIANGLES, lastIndexPlace, GL_UNSIGNED_INT, (void*)0);
	}
}
