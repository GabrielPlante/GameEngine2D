#include "UniformHandler.h"
#include <GL/glew.h>

#ifdef DEBUG_GE
#include <iostream>
#endif //DEBUG_GE

namespace ge {
	UniformHandler::UniformHandler(const std::vector<std::string>& uniformNames)
		: uniformNames{ uniformNames }
	{}

	void UniformHandler::computeUniformID(uint32_t shaderID)
	{
		for (auto uniformName : uniformNames) {
			int uniformID = glGetUniformLocation(shaderID, uniformName.c_str());
#ifdef DEBUG_GE
			if (uniformID == -1) {
				std::cout << "Location not found of the uniform: " << uniformName << std::endl;
			}
#endif // DEBUG_GE
			uniformIDs.push_back(uniformID);
		}
	}
}
