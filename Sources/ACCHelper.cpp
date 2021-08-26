#include "ACCHelper.h"
#include "Common/ACC.h"

#include <iostream>
#include <tchar.h>

namespace ACC {

    TCHAR shmname_physics[] = TEXT("Local\\acpmf_physics");
    TCHAR shmname_graphics[] = TEXT("Local\\acpmf_graphics");
    TCHAR shmname_static[] = TEXT("Local\\acpmf_static");

    ACCHelper::ACCHelper()
    {
        initPhysics();
        initGraphics();
        initStatic();
    }

    ACCHelper::~ACCHelper()
    {
        cleanup();
    }

    ACCStatus ACCHelper::getUpdate()
    {
        SPageFilePhysics* pagePhysics = (SPageFilePhysics*)shmPhysics.buffer;
        SPageFileGraphic* pageGraphics = (SPageFileGraphic*)shmGraphics.buffer;
        SPageFileStatic* pageStatic = (SPageFileStatic*)shmStatic.buffer;

        ACCStatus status;
        
        status.lights = pageGraphics->lightsStage;
        
        return status;
    }

    bool ACCHelper::initPhysics()
    {
        shmPhysics.handle = CreateFileMapping(
            INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
            0, sizeof(SPageFilePhysics), shmname_physics);

        if (!shmPhysics.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_physics << std::endl;
            return false;
        }

        shmPhysics.buffer = (unsigned char*)MapViewOfFile(
            shmPhysics.handle, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));

        if (!shmPhysics.handle) {
            std::cerr << "MapViewOfFile failed for " << shmname_physics << std::endl;
            return false;
        }
        return true;
    }

    bool ACCHelper::initGraphics()
    {
        shmGraphics.handle = CreateFileMapping(
            INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
            0, sizeof(SPageFileGraphic), shmname_graphics);

        if (!shmGraphics.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_graphics << std::endl;
            return false;
        }

        shmGraphics.buffer = (unsigned char*)MapViewOfFile(
            shmGraphics.handle, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic));

        if (!shmGraphics.handle) {
            std::cerr << "MapViewOfFile failed for " << shmname_graphics << std::endl;
            return false;
        }
        return true;
    }

    bool ACCHelper::initStatic()
    {
        shmStatic.handle = CreateFileMapping(
            INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
            0, sizeof(SPageFileStatic), shmname_static);

        if (!shmStatic.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_static << std::endl;
            return false;
        }

        shmStatic.buffer = (unsigned char*)MapViewOfFile(
            shmStatic.handle, FILE_MAP_READ, 0, 0, sizeof(SPageFileStatic));

        if (!shmStatic.handle) {
            std::cerr << "MapViewOfFile failed for " << shmname_static << std::endl;
            return false;
        }
        return true;
    }

    void ACCHelper::cleanup()
    {
        std::cout << "Cleaning up" << std::endl;
        UnmapViewOfFile(shmPhysics.buffer);
        CloseHandle(shmPhysics.handle);
        UnmapViewOfFile(shmGraphics.buffer);
        CloseHandle(shmGraphics.handle);
        UnmapViewOfFile(shmStatic.buffer);
        CloseHandle(shmStatic.handle);
    }

} // namespace ACC