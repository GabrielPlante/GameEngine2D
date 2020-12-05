#pragma once
#include <unordered_map>

#include "IDGenerator.h"
#include "Vector2.h"
#include "System.h"
#include "Shader.h"

namespace ge {
    class BatchRenderer;
    class DefaultGraphicSystem :
        public System
    {
    private:
        //Temp
        Shader defaultShader;
    public:
		//Constructor
		DefaultGraphicSystem(Shader&& defaultShader);

        //Render
        void update() override;

        //Add a batch renderer and get his id back.
        uint32_t addBatchRenderer(BatchRenderer* batchRenderer);
    };

}
