#pragma once

#include <Windows.h>

namespace ACC {

    struct SHMElement
    {
        HANDLE handle;
        unsigned char* buffer;
    };

    struct ACCStatus {
        int lights;
    };

    class ACCHelper {
    public:
        ACCHelper();
        virtual ~ACCHelper();

        ACCStatus getUpdate();

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