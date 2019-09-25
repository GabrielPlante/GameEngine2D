#pragma once
#include <SDL.h>

#include "Color.h"

namespace ge {
	//Used to start and stop the sdl text input
	struct TextInput
	{
	public:
		//Constructor, start the SDL text input
		TextInput() { SDL_StartTextInput(); }

		//Destructor, stop the SDL text input
		~TextInput() { SDL_StopTextInput(); }
	};

}
