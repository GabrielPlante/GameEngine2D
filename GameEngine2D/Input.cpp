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
	std::unordered_map<std::string, bool> Input::toggleCommand;

	void Input::init(Window* window) {
		//Set the key callback for the event system
		glfwSetKeyCallback(*window, [](GLFWwindow*, int, int scancode, int action, int mods) -> void {
			Input::keyEvent(scancode, action, mods);
		});
	}

	void Input::bindKey(int scancode, const std::string& commandName, bool toggle) {
		keyMap[scancode] = commandName;
		//If the command is toggling, add it to the list
		if (toggle)
			toggleCommand.insert(std::make_pair(commandName, false));
	}

	void Input::bindKey(int scancode, const std::string& commandName, std::function<void(const std::vector<float>&)> commandFunction, bool toggle) {
		ADD_COMMAND(commandName, commandFunction);
		bindKey(scancode, commandName, toggle);
	}

	void Input::update()
	{
		for (auto command : toggleCommand)
			if (command.second)
				CommandList::getInstance()->executeCommand(command.first, {});
	}

	void Input::keyEvent(int scancode, int action, int mods)
	{
		auto commandNameIt{ keyMap.find(scancode) };
		//If the scancode is assigned to a command and it is not a toggle
		if (commandNameIt != keyMap.end() && toggleCommand.find(commandNameIt->second) == toggleCommand.end())
			CommandList::getInstance()->executeCommand(keyMap.find(scancode)->second, { static_cast<float>(action), static_cast<float>(mods) });
		//If the command is assigned to a toggle, set the toggle according to the action
		else if (commandNameIt != keyMap.end())
			toggleCommand.find(commandNameIt->second)->second = action != GLFW_RELEASE;
#ifdef DEBUG_GE
		else
			std::cout << "Key with scancode " << scancode << " not found" << std::endl;
#endif //DEBUG_GE
	}
}
