#include "DefaultGraphicSystem.h"

#include "CommandList.h"

namespace ge {
	DefaultGraphicSystem::DefaultGraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
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

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        /* Loop until the user closes the window */
        if (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        else {
            EXEC("quit");
        }
	}
}
