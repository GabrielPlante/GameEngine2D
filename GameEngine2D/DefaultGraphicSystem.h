#pragma once

#include "System.h"
#include "Window.h"

namespace ge {
    class DefaultGraphicSystem :
        public System
    {
    private:
		Window window;
    public:
		//Constructor
		DefaultGraphicSystem(int screenWidth, int screenHeight);

        //Render
        void update() override;
    };

}
