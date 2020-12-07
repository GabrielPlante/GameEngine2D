#pragma once

#include "System.h"

namespace ge {
    class DefaultGraphicSystem :
        public System
    {
    public:
		//Constructor
		DefaultGraphicSystem();

        //Render
        void update() override;
    };

}
