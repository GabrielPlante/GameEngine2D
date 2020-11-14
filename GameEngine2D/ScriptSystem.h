#pragma once
#include "System.h"

namespace ge {
    class ScriptSystem :
        public System
    {
    public:
        //Update the script
        void update() override;
    };
}
