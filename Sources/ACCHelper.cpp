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

    GameState ACCHelper::getUpdate()
    {
        raw::SPageFilePhysics* pagePhysics = (raw::SPageFilePhysics*)shmPhysics.buffer;
        raw::SPageFileGraphic* pageGraphics = (raw::SPageFileGraphic*)shmGraphics.buffer;
        raw::SPageFileStatic* pageStatic = (raw::SPageFileStatic*)shmStatic.buffer;

        GameState state;
        
        //Headlights
        switch (pageGraphics->lightsStage) {
        case 0:
            state.headlights = GameState::Headlights::Off;
            break;
        case 1:
            state.headlights = GameState::Headlights::LowBeam;
            break;
        case 2:
            state.headlights = GameState::Headlights::HighBeam;
            break;
        default:
            state.headlights = GameState::Headlights::Off;
            break;
        }

        //RainLight
        switch (pageGraphics->rainLights) {
        case 0:
            state.rainLight = GameState::RainLight::Off;
            break;
        case 1:
            state.rainLight = GameState::RainLight::On;
            break;
        default:
            state.rainLight = GameState::RainLight::Off;
            break;
        }
        
        return state;
    }

    bool ACCHelper::initPhysics()
    {
        shmPhysics.handle = CreateFileMapping(
            INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
            0, sizeof(raw::SPageFilePhysics), shmname_physics);

        if (!shmPhysics.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_physics << std::endl;
            return false;
        }

        shmPhysics.buffer = (unsigned char*)MapViewOfFile(
            shmPhysics.handle, FILE_MAP_READ, 0, 0, sizeof(raw::SPageFilePhysics));

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
            0, sizeof(raw::SPageFileGraphic), shmname_graphics);

        if (!shmGraphics.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_graphics << std::endl;
            return false;
        }

        shmGraphics.buffer = (unsigned char*)MapViewOfFile(
            shmGraphics.handle, FILE_MAP_READ, 0, 0, sizeof(raw::SPageFileGraphic));

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
            0, sizeof(raw::SPageFileStatic), shmname_static);

        if (!shmStatic.handle) {
            std::cerr << "CreateFileMapping failed for " << shmname_static << std::endl;
            return false;
        }

        shmStatic.buffer = (unsigned char*)MapViewOfFile(
            shmStatic.handle, FILE_MAP_READ, 0, 0, sizeof(raw::SPageFileStatic));

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