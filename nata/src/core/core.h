#pragma once
#include "core/ecs/ecs.h"
#include "nata_math.h"

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
    T* Instantiate(NWorld* world, bool enable = true)
    {
        return world->Instantiate<T>(enable);
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    T* Instantiate(NWorld* world, vec3 position, bool enable = true)
    {

        return world->Instantiate<T>(position, enable);
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    T* Instantiate(NWorld* world, vec3 position, vec3 rotation, bool enable = true)
    {
        return world->Instantiate<T>(position, rotation, enable);
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
    std::vector<T*> GetAllEntitiesOfType(NWorld* world)
    {
        std::vector<T*> entities;
        for (EEntity* entity : NEngine::World->GetAllEntities())
        {
            if (typeid(*entity).name() == typeid(T).name())
            {
                entities.push_back((T*)entity);
            }
        }
        return entities;
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
    std::vector<T*> GetAllComponentsOfType(NWorld* world)
    {
        std::vector<T*> components;
        for (EEntity* entity : world->GetAllEntities())
        {
            T* component = entity->GetComponent<T>();
            if (component != nullptr)
            {
                components.push_back(component);
            }
        }
        return components;
    }

    template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
    std::vector<T*> GetAllEnabledComponentsOfType(NWorld* world)
    {
        std::vector<T*> components;
        for (EEntity* entity : world->GetAllEnabledEntities())
        {
            T* component = entity->GetComponent<T>();
            if (component != nullptr)
            {
                components.push_back(component);
            }
        }
        return components;
    }

    static void SetEnable(EEntity* entity, bool enable)
    {
        entity->Super_SetEnable(enable);
    }

    static void SetEnable(CComponent* component, bool enable)
    {
        component->Super_SetEnable(enable);
    }

    void Destroy(NWorld* world, EEntity* entity);
}