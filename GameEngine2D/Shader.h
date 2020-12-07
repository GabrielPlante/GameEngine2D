#pragma once
#include <vector>
#include <string>
#include <array>

namespace ge {
	class Shader {
	private:
		uint32_t shaderID;

		std::vector<int> uniformsID;
		std::vector<std::array<float, 4>(*)()> uniformsValues;

		//Transform the uniform name into their ID
		void setupUniforms(const std::vector<std::string>& uniforms);
	public:
		//Constructor, take vertex and fragment program in parameter, as well as a list of uniforms name and a function for each to retrieve right values before executing the shader
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc, const std::vector<std::string>& uniforms = {}, const std::vector<std::array<float, 4>(*)()>& uniformsValues = {});

		//Move constructor && operator
		Shader(Shader&& shader) : shaderID{ shader.shaderID } { shader.shaderID = 0; }
		Shader& operator=(Shader&& shader) { shaderID = shader.shaderID; shader.shaderID = 0; }

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
