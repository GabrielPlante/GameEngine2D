#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

namespace ge {
	class Window;
	//Static class to handle input. The method update need to be called each frame
	struct Input
	{
	private:
		static std::unordered_map<int, std::string> keyMap;

		//The map that hold every command that toggle (ie called each frame if the key is pressed) and the bool that represent if the key is pressed
		static std::unordered_map<std::string, bool> toggleCommand;
	public:
		//Initialise the input system
		static void init(Window* window);

		//Bind a key to an existing command. Set toggle to true to have the command called each frame when the key is pressed
		static void bindKey(int scancode, const std::string& commandName, bool toggle = false);
		//Bind a key to a new command. Set toggle to true to have the command called each frame when the key is pressed
		static void bindKey(int scancode, const std::string& commandName, std::function<void(const std::vector<float>&)> commandFunction, bool toggle = false);

		//Update the input system, it need to be called every frame
		static void update();

		//Execute a command given the key, with the args vector filled with the action and the mods
		//If toggle is set to true, the command will be executed each frame once the key is pressed, stopping when the key is released
		static void keyEvent(int scancode, int action, int mods);
	};
}

