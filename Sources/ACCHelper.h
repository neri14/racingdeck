#pragma once

#include <Windows.h>
#include "GameState.h"

namespace ACC {
    struct SHMElement
    {
        HANDLE handle;
        unsigned char* buffer;
    };

    class ACCHelper {
    public:
        ACCHelper();
        virtual ~ACCHelper();

        GameState getUpdate();

    private:
        bool initPhysics();
        bool initGraphics();
        bool initStatic();
        void cleanup();

        SHMElement shmPhysics;
        SHMElement shmGraphics;
        SHMElement shmStatic;
    };

} // namespace ACC