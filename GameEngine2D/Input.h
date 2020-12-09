#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

namespace ge {
	class Window;
	struct Input
	{
	private:
		static std::unordered_map<int, std::string> keyMap;
	public:
		//Initialise the input system
		static void init(Window* window);

		//Bind a key to an existing command
		static void bindKey(int scancode, const std::string& commandName);
		//Bind a key to a new command
		static void bindKey(int scancode, const std::string& commandName, std::function<void(const std::vector<float>&)> commandFunction);

		//Execute a command given the key
		static void keyEvent(int scancode, int action, int mods);
	};
}

