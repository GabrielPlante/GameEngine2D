#include "Engine.h"
#include <stdexcept>
#include <GLFW/glfw3.h>

#include <iostream>

namespace ge {
	Engine::Init::Init() {
		if (!glfwInit())
			throw std::runtime_error("Could not initialise GLFW");
	}

	Engine::Init::~Init() {
		glfwTerminate();
	}
}
