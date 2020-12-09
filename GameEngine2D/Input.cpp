#include "Input.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CommandList.h"
#include "Window.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	std::unordered_map<int, std::string> Input::keyMap;

	void Input::init(Window* window) {
		//Set the key callback for the event system
		glfwSetKeyCallback(*window, [](GLFWwindow*, int, int scancode, int action, int mods) -> void {
			Input::keyEvent(scancode, action, mods);
		});
	}

	void Input::bindKey(int scancode, const std::string& commandName) {
		keyMap[scancode] = commandName;
	}

	void Input::bindKey(int scancode, const std::string& commandName, std::function<void(const std::vector<float>&)> commandFunction) {
		ADD_COMMAND(commandName, commandFunction);
		bindKey(scancode, commandName);
	}

	void Input::keyEvent(int scancode, int action, int mods)
	{
		if (keyMap.find(scancode) != keyMap.end())
			CommandList::getInstance()->executeCommand(keyMap.find(scancode)->second, { static_cast<float>(action), static_cast<float>(mods) });
#ifdef DEBUG_GE
		else
			std::cout << "Key with scancode " << scancode << " not found" << std::endl;
#endif //DEBUG_GE
	}
}
