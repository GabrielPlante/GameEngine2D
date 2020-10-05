#pragma once
#include "TextureCreator.h"

namespace ge {
    class HexagonCreator :
        public TextureCreator
    {
    public:
        HexagonCreator(int size, Color color, bool blend = true);
    };

}
