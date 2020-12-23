#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector2.h"

namespace ge {
	class Window
	{
	private:
		GLFWwindow* window;

	public:
		//Constructor
		Window(const int screenWidth, const int screenHeight, const std::string& title = "Ianagd");

		//Implicit conversion to the GLFWwindow type
		operator GLFWwindow*() { return window; }

		Vector2<int> getWindowSize() const;

		//Destructor
		~Window();
	};
}
