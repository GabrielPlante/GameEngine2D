#include "DefaultGraphicSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BatchRenderer.h"
#include "CommandList.h"
#include "Storage.h"
#include "Engine.h"

#ifdef DEBUG_GE
#include <iostream>

void glErrorHandling(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei,
    const GLchar* message,
    const void*) {
    
    std::cout << "An error occured with OpenGL:\nError source: " << source << ", type: " << type << ", ID: " << id << ", severity: " << severity << std::endl;
    std::cout << "Message: " << message << std::endl;
}
#endif

#include "Vector2.h"

namespace ge {
	DefaultGraphicSystem::DefaultGraphicSystem()
    {
#ifdef DEBUG_GE
        //Enable OpenGL debuging
        glDebugMessageCallback(glErrorHandling, NULL);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageControl(
            GL_DEBUG_SOURCE_API,
            GL_DONT_CARE,
            GL_DONT_CARE,
            0, NULL,
            GL_FALSE); // disable all messages with source `GL_DEBUG_SOURCE_APPLICATION`
#endif
	}

    void DefaultGraphicSystem::update()
    {
        /* Loop until the user closes the window */
        if (!glfwWindowShouldClose(ENGINE->getWindow()))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //Render every batch
            for (auto it = Storage<BatchRenderer*>::begin(); it != Storage<BatchRenderer*>::end(); it++) {
                (*it)->renderBatch();
            }

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
