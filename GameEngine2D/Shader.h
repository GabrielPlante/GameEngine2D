#pragma once
#include <string>

namespace ge {
	class Shader {
	private:
		uint32_t shaderID;

	public:
		//Constructor, take vertex and fragment program in parameter
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		//Move constructor && operator
		Shader(Shader&& shader) : shaderID{ shader.shaderID } { shader.shaderID = 0; }
		Shader& operator=(Shader&& shader) { shaderID = shader.shaderID; shader.shaderID = 0; }

		//Delete copy constructor && assignments
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;

		void unbind() const;

		//Destroy shader
		~Shader();
	};
}
