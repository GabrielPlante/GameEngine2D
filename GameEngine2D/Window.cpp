#include "Window.h"
#include <stdexcept>

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	Window::Window(const int screenWidth, const int screenHeight, const std::string& title)
	{
#ifdef DEBUG_GE
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			throw std::runtime_error("Could not create a window");
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialise GLEW");

		//When the window is resized, update OpenGL
		glfwSetFramebufferSizeCallback(*this, [](GLFWwindow*, int width, int height) -> void {
			glViewport(0, 0, width, height);
			});

		//std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
	}


	Vector2<int> Window::getWindowSize() const
	{
		//Fetch the size from glfw. Might be optimised by using an attribute tied to a callback
		Vector2<int> windowSize;
		glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
		return windowSize;
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}
}

