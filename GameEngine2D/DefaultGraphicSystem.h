#pragma once
#include <unordered_map>

#include "IDGenerator.h"
#include "Vector2.h"
#include "System.h"

namespace ge {
    class BatchRenderer;
    class DefaultGraphicSystem :
        public System
    {
    private:
    public:
		//Constructor
		DefaultGraphicSystem();

        //Render
        void update() override;
    };

}
