#pragma once
#include <vector>
#include "core/glm_math.h"

using namespace std;

namespace Nata
{
	class NGameMode;
	class NWorld;
	class NEntity;
	class NComponent;

	class NEntity
	{
	private:
		NWorld* m_World;
		vector<NComponent*> m_Components;

	public:
		NEntity() {}

		NEntity(NWorld* world)
		{
			m_World = world;
		}

		NWorld* GetWorld() { return m_World; }
		void SetWorld(NWorld* world) { m_World = world; }

		template<typename T, class = typename std::enable_if<std::is_base_of<NComponent, T>::value>::type>
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
			for (NComponent* comp : m_Components)
			{
				if (typeid(*comp).name() == typeid(T).name())
				{
					return (T*)comp;
				}
			}
		}

		vector<NComponent*> GetALlComponents()
		{
			return m_Components;
		}

		virtual void Begin();
		virtual void Tick();
	};

	class NComponent
	{
	private:
		NEntity* m_Owner;

		friend class NEntity;

	public:
		NComponent() {}

		NComponent(NEntity* owner)
		{
			m_Owner = owner;
		}

		NEntity* GetOwner() { return m_Owner; }
		void SetOwner(NEntity* owner) { m_Owner = owner; }

		virtual void Begin();
		virtual void Tick();
	};

	// behaviour in level lifetime
	class NGameMode
	{
	private:
		NWorld* m_World;

	public:
		NGameMode(){}

		NWorld* GetWorld() { return m_World; }
		void SetWorld(NWorld* world) { m_World = world; }

		virtual void Begin();
		virtual void Tick();
	};

	// behaviour in application lifetime
	class NGameInstance
	{
	public:
		virtual void Begin();
		virtual void Tick();
	};

	class NWorld
	{
	private:
		NGameMode* m_GameMode;
		vector<NEntity*> m_Entities;

	public:
		NWorld(){}

		vector<NEntity*> GetAllEntities() { return m_Entities; }
		void SetGameMode(NGameMode* gameMode) { m_GameMode = gameMode; }

		void Begin()
		{
			m_GameMode->Begin();
			for (NEntity* entity : m_Entities)
			{
				entity->Begin();
			}
		}

		void Tick()
		{
			m_GameMode->Tick();
			for (NEntity* entity : m_Entities)
			{
				entity->Tick();
			}
		}
	};
} 