#include "Window.h"
#include <SDL_ttf.h>
//#include <Windows.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <stdexcept>


namespace ge {
	Window::Window(const int screenWidth, const int screenHeight)
		:screenWidth{ screenWidth }, screenHeight{ screenHeight }
	{
		//Shader loading utility programs
		void printProgramLog(GLuint program);
		void printShaderLog(GLuint shader);

		if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
			throw std::runtime_error("Failed to set SDL_GL_CONTEXT_MAJOR_VERSION");

		if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6))
			throw std::runtime_error("Failed to set SDL_GL_CONTEXT_MINOR_VERSION");

		if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
			throw std::runtime_error("Failed to set SDL_GL_CONTEXT_PROFILE_CORE");

		//Create window
		gWindow = SDL_CreateWindow("Ianagd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (!gWindow)
			throw std::runtime_error("SDL_CreateWindow failed");

		//Create renderer
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!gRenderer)
			throw std::runtime_error("SDL_CreateRenderer failed");

		//Everything will be painted black
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

		//Alpha blending https://wiki.libsdl.org/SDL_BlendMode
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	}

	Window::~Window()
	{
		//Destroy
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gRenderer = nullptr;
		gWindow = nullptr;
	}
}
