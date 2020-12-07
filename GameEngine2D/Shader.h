#pragma once
#include <memory>
#include <vector>
#include <string>
#include <array>

#include "UniformHandler.h"

namespace ge {
	class Shader {
	private:
		uint32_t shaderID;

		std::vector<std::unique_ptr<UniformHandler>> uniforms;

		//Transform the uniform name into their ID
		void setupUniforms();
	public:
		//Constructor, take vertex and fragment program in parameter, as well as a list of uniforms
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc, std::vector<std::unique_ptr<UniformHandler>>&& uniforms);

		//Move constructor && operator
		Shader(Shader&& shader);
		Shader& operator=(Shader&& shader);

		//Delete copy constructor && assignments
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		//Bind the shader to the OpenGL constext
		void bind() const;

		//Bind the uniform and set their values
		void bindUniforms() const;

		void unbind() const;

		//Destroy shader
		~Shader();
	};
}
