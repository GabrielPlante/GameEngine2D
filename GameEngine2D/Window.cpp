#include "Window.h"
#include <stdexcept>

#include <iostream>

namespace ge {
	Window::Window(const int screenWidth, const int screenHeight, const std::string& title)
	{
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

		//std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
	}


	Window::~Window()
	{
		glfwDestroyWindow(window);
	}
}

