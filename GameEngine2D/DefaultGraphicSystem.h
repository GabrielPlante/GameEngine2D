#pragma once

#include "System.h"
#include "Shader.h"

namespace ge {
    class DefaultGraphicSystem :
        public System
    {
    private:
        Shader defaultShader;
    public:
		//Constructor
		DefaultGraphicSystem(Shader&& defaultShader);

        //Render
        void update() override;
    };

}
