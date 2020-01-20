#include "Window.h"
#include <SDL_ttf.h>
//#include <Windows.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/GL.h>
#include <stdexcept>

#pragma comment(lib, "glew32.lib")



void initGL() {
	//Graphics program
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	//Success flag

	//Generate program
	gProgramID = glCreateProgram();
	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
		throw std::runtime_error{ "Unable to compile vertex shader" };

	//Attach vertex shader to program
	glAttachShader(gProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Get fragment source
	const GLchar* fragmentShaderSource[] =
	{
		"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
	};

	//Set fragment source
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

	//Compile fragment source
	glCompileShader(fragmentShader);

	//Check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
		throw std::runtime_error{ "Unable to compile fragment shader" };

	//Attach fragment shader to program
	glAttachShader(gProgramID, fragmentShader);


	//Link program
	glLinkProgram(gProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
		throw std::runtime_error{ "Error linking program" };

	//Get vertex attribute location
	gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
	if (gVertexPos2DLocation == -1)
		throw std::runtime_error{ "LVertexPos2D is not a valid glsl program variable!" };

	//Initialize clear color
	//glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data
	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	//IBO data
	GLuint indexData[] = { 0, 1, 2, 3 };

	//Create VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//Create IBO
	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
}

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
		gWindow = SDL_CreateWindow("Ianagd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
		if (!gWindow)
			throw std::runtime_error("SDL_CreateWindow failed");

		gContext = SDL_GL_CreateContext(gWindow);
		if(!gContext)
			throw std::runtime_error("SDL_GL_CreateContext failed");

		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
			throw std::runtime_error("glewInit failed");

		//Init OpenGL
		initGL();


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

