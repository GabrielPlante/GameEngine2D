#pragma once
#include "TextureCreator.h"

#include "Vector2.h"

namespace ge {
    class RectangleCreator :
        public TextureCreator
    {
    public:
        RectangleCreator(Vector2<int> size, Color color, bool fill = true, bool blend = true);
    };
}
