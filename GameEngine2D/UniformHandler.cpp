#include "UniformHandler.h"
#include <GL/glew.h>

#ifdef DEBUG_GE
#include <iostream>
#endif //DEBUG_GE

namespace ge {
	UniformHandler::UniformHandler(const std::string& uniformName)
		: uniformName{ uniformName }
	{}

	void UniformHandler::computeUniformID(uint32_t shaderID)
	{
		uniformID = glGetUniformLocation(shaderID, uniformName.c_str());
#ifdef DEBUG_GE
		if (uniformID == -1) {
			std::cout << "Location not found of the uniform: " << uniformName << std::endl;
		}
#endif // DEBUG_GE
	}
}
