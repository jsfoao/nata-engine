#pragma once
#include "core/ecs/ecs.h"
#include "core/glm_math.h"

namespace Nata
{
    class NTime
    {
    public:
        static float Time;
        static float DeltaTime;
    };

    class NEngine
    {
    public:
        static class NWindow* Window;
        static class NInput* Input;
        static class CCamera* ActiveCamera;
        static float WindowSizeX;
        static float WindowSizeY;
    };

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    T* Instantiate(NWorld* world)
    {
        return world->Instantiate<T>();
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    T* Instantiate(NWorld* world, vec3 position)
    {
        return world->Instantiate<T>(position);
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    T* Instantiate(NWorld* world, vec3 position, vec3 rotation)
    {
        return world->Instantiate<T>(position, rotation);
    }

    void Destroy(NWorld* world, EEntity* entity);
}