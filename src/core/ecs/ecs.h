#pragma once
#include <vector>
#include "core/glm_math.h"

using namespace std;

namespace Nata
{
	class World;
	class Entity;
	class Component;

	class Component
	{
	private:
		Entity* m_Owner;

		friend class Entity;

	public: 
		Component(Entity* owner)
		{
			m_Owner = owner;
		}

		Entity* GetOwner()
		{
			return m_Owner;
		}

		virtual void Begin();
		virtual void Tick();
	};

	class Entity
	{
	private:
		World* m_World;
		vector<Component*> m_Components;

	public:
		Entity(World* world)
		{
			m_World = world;
		}

		World* GetWorld()
		{
			return m_World;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
		T* AddComponent()
		{
			T* newComp = new T();
			newComp->m_Owner = this;
			m_Components.push_back(newComp);
			return newComp;
		}

		template<typename T>
		T* GetComponent()
		{
			for (Component* comp : m_Components)
			{
				if (typeid(*comp).name() == typeid(T).name())
				{
					return (T*)comp;
				}
			}
		}

		virtual void Begin();
		virtual void Tick();
		virtual void OnDestroy();
	};
} 