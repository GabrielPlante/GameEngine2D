#pragma once
#include <string>
#include <GLFW/glfw3.h>

namespace ge {
	class Window
	{
	private:
		const int screenWidth;
		const int screenHeight;

		GLFWwindow* window;
	public:
		//Constructor
		Window(const int screenWidth, const int screenHeight, const std::string& title = "Ianagd");

		operator GLFWwindow*() { return window; }

		//Destructor
		~Window();
	};
}
