#include "DefaultGraphicSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CommandList.h"
#include "Renderer.h"
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

namespace ge {
	DefaultGraphicSystem::DefaultGraphicSystem(Shader&& defaultShader)
        : defaultShader{ std::move(defaultShader) }
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
        constexpr int size{ 8 };
        float position[size] = {
            0.0f, -0.5f,
            0.0f,  0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
        };

        constexpr int iSize{ 6 };
        unsigned int indices[iSize] = {
            0, 1, 2,
            1, 2, 3
        };
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), position, GL_STATIC_DRAW);

        unsigned int ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        /*defaultShader.bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);*/

        /* Loop until the user closes the window */
        if (!glfwWindowShouldClose(ENGINE->getWindow()))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //glDrawArrays(GL_TRIANGLES, 0, 3);
            Renderer::render(&defaultShader, iSize);

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
