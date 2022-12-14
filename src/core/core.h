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
        // Active camera component
        static class CCamera* Camera;
        // Active world
        static class NWorld* World;
        static int WindowSizeX;
        static int WindowSizeY;
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

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    std::vector<T*> GetEntitiesOfType(NWorld* world)
    {
        std::vector<T*> entities;
        for (EEntity* entity : NEngine::World->GetAllEntities())
        {
            if (typeid(*entity).name() == typeid(T).name())
            {
                entities.push_back(entity);
            }
        }
        return entities;
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<CComponent>::value>::type>
    std::vector<T*> GetComponentsOfType(NWorld* world)
    {
        std::vector<T*> components;
        for (EEntity* entity : NEngine::World->GetAllEntities())
        {
            CComponent* component = entity->GetComponent<T>();
            if (component != nullptr)
            {
                components.push_back(component);
            }
        }
        return components;
    }

    void Destroy(NWorld* world, EEntity* entity);
}