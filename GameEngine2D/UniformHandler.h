#pragma once
#include <string>

namespace ge {
	//UniformHandler is a base class for any class that want to have a uniform tied to it
	//Implement updateIniform to handle the correct way the uniform
	class UniformHandler {
	private:
		std::string uniformName;

	protected:
		int uniformID{ -1 };

	public:
		//Constructor
		UniformHandler(const std::string& uniformName);

		//Compute the uniform id, used once by the shader
		void computeUniformID(uint32_t shaderID);

		//This method is called right after the shader is bound, each frame. The uniform is supposed to update it's content to OpenGL
		virtual void updateUniform() const = 0;
	};
}
