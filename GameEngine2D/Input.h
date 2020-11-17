#pragma once
#include "Vector2.h"

#define MOUSE ge::Input::Mouse

constexpr char MOUSE_LEFT{ 0 };
constexpr char MOUSE_RIGHT{ 1 };

namespace ge {
	struct Input
	{
	public:
		struct Mouse {
			static bool isMouseLeftPressed;
			static bool isMouseRightPressed;
		public:
			//Get the mouse position on the screen
			static ge::Vector2<int> getMousePosition();

			//Is a mouse button pressed
			static bool isMouseButtonPressed(char button);
		};
	};
}

