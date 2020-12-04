#include "Renderer.h"

#include <GL/glew.h>

namespace ge::Renderer {
	void render(Shader* shader, int count) {
        //Bind the shader and set the parameters for the array
        shader->bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        //glDrawArrays(GL_TRIANGLES, 0, count);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

        shader->unbind();
	}
}
