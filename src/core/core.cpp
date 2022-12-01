#include "core.h"

namespace Nata
{
    float NTime::Time = 0.f;
    float NTime::DeltaTime = 0.f;
    NWindow* NEngine::Window = nullptr;
    NInput* NEngine::Input = nullptr;
    CCamera* NEngine::Camera = nullptr;
    NWorld* NEngine::World = nullptr;
    int NEngine::WindowSizeX = 700.f;
    int NEngine::WindowSizeY = 500.f;

    void Destroy(NWorld* world, EEntity* entity)
    {
        world->Destroy(entity);
    }
}