#include "Window.h"
#include <stdexcept>
#include <GLFW/glfw3.h>

namespace ge {
	Window::Window(const int screenWidth, const int screenHeight, const std::string& title)
		:screenWidth{ screenWidth }, screenHeight{ screenHeight }
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
	}


	Window::~Window()
	{
	}
}

