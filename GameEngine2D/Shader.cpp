#include "Shader.h"
#include <vector>
#include <GL/glew.h>

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	void Shader::setupUniforms()
	{
		for (int i = 0; i != uniforms.size(); i++) {
			uniforms[i]->computeUniformID(shaderID);
		}
	}

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, std::vector<std::unique_ptr<UniformHandler>>&& uniforms)
		: uniforms{ std::move(uniforms) }
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			std::cout << "Vertex shader compilation error : " << infoLog.data() << std::endl;

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			std::cout << "Fragment shader compilation error : " << infoLog.data() << std::endl;

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		shaderID = glCreateProgram();
		GLuint program = shaderID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			std::cout << "Shader linking error : " << infoLog.data() << std::endl;

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		//Setup the uniforms (aka transform their names into ids
		setupUniforms();
	}

	Shader::Shader(Shader&& shader)
		: shaderID{ shader.shaderID }, uniforms{ std::move(shader.uniforms) }
	{
		shader.shaderID = 0;
	}

	void Shader::bind() const
	{
		glUseProgram(shaderID);
	}

	void Shader::bindUniforms() const
	{
		for (int i = 0; i != uniforms.size(); i++) {
			uniforms[i]->updateUniform();
		}
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		if (shaderID != 0)
			glDeleteProgram(shaderID);
	}

	Shader& Shader::operator=(Shader&& shader)
	{
		shaderID = shader.shaderID;
		uniforms = std::move(shader.uniforms);
		shader.shaderID = 0;

		return *this;
	}
}