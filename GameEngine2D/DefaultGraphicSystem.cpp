#include "DefaultGraphicSystem.h"

#include "CommandList.h"

namespace ge {
	DefaultGraphicSystem::DefaultGraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{
	}

	void DefaultGraphicSystem::update()
	{
        /* Loop until the user closes the window */
        if (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

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
