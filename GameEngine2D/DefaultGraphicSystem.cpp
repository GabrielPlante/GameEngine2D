#include "DefaultGraphicSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CommandList.h"
#include "Engine.h"

namespace ge {
	DefaultGraphicSystem::DefaultGraphicSystem(Shader&& defaultShader)
        : defaultShader{ std::move(defaultShader) }
	{
	}

	void DefaultGraphicSystem::update()
	{
        float position[6] = {
           -0.5f, -0.5f,
            0.0f,  0.5f,
            0.5f, -0.5f
        };
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

        defaultShader.bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        /* Loop until the user closes the window */
        if (!glfwWindowShouldClose(ENGINE->getWindow()))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(ENGINE->getWindow());

            /* Poll for and process events */
            glfwPollEvents();
        }
        else {
            EXEC("quit");
        }
	}
}
