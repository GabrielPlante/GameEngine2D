#include "TextureWrapper.h"

namespace ge {
	IDGenerator<> TextureWrapper::idGenerator{};
	std::map<unsigned int, int> TextureWrapper::instanceCounter{};
}