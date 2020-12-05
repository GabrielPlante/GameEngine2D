#pragma once

#include "System.h"
#include "Shader.h"
#include "Batch.h"
#include "Vector2.h"

namespace ge {
    class DefaultGraphicSystem :
        public System
    {
    private:
        Shader defaultShader;
        Batch<Vector2<float>, 1, 4, 6> squareBatch;
    public:
		//Constructor
		DefaultGraphicSystem(Shader&& defaultShader);

        //Render
        void update() override;
    };

}
