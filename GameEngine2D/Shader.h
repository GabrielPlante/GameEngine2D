#pragma once
#include <string>

namespace ge {
	class Shader {
	private:
		uint32_t shaderID;

	public:
		//Constructor, take vertex and fragment program in parameter
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		void bind() const;

		void unbind() const;

		//Destroy shader
		~Shader();
	};
}
