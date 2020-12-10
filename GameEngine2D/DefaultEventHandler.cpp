#include "DefaultEventHandler.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Input.h"

#include <iostream>

namespace ge {
	DefaultEventHandler::DefaultEventHandler() {
	}

	void DefaultEventHandler::update()
	{
		Input::update();
	}
}
