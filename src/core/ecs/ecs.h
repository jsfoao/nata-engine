#pragma once
#include <vector>
#include <queue>
#include "core/glm_math.h"
#include <iostream>

using namespace std;

namespace Nata
{
	class GGameMode;
	class NWorld;
	class NObject;
	class EEntity;
	class CComponent;

	// 0 is reserved to CTransform
	static unsigned int CComponentID = 1;
#define GENERATE_COMPONENT public: static unsigned int TypeID
#define INIT_COMPONENT(T) unsigned int T::TypeID = 0;
#define INIT_ID(T) m_TypeID = TypeID

	// Everything that is instanced, has ID and is serialized in engine
	class NObject
	{
	public:
		unsigned int ID;
	};

	// Entity components
	class CComponent : public NObject
	{
	protected:
		EEntity* m_Owner;
		bool m_Enabled;
		unsigned int m_TypeID = 0;

		friend class EEntity;

	public:
		CComponent();
		CComponent(EEntity* owner);

		inline unsigned int GetTypeID() { return m_TypeID; }
		inline EEntity* GetOwner() { return m_Owner; }
		inline void SetOwner(EEntity* owner) { m_Owner = owner; }
		inline void SetEnabled(bool enabled) { m_Enabled = enabled; }

		virtual void Begin() {};
		virtual void Tick(float dt) {};
		void SuperBegin();
		void SuperTick(float dt);
	};

	//std::vector<CComponent> CompRegistry;
	//template<typename T>
	//void CompRegister()
	//{
	//	if (CompRegistry.size() == 0) 
	//	{
	//		CompRegistry.push_back(T);
	//		T::TypeID = CComponentID;
	//		return;
	//	}
	//	for (unsigned int i = 0; i < CompRegistry.size(); i++)
	//	{
	//		if (typeid(T).name == typeid(CompRegistry[i]).name)
	//		{
	//			return;
	//		}
	//	}
	//	CompRegistry.push_back(T);
	//	T::TypeID = CComponentID;
	//	CComponentID++;
	//}

	class CTransform : public CComponent
	{
		GENERATE_COMPONENT;
	public:
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;
		vec3 LocalPosition;

		vec3 Forward;
		vec3 Right;
		vec3 Up;
		
		CTransform* Parent;
		vector<CTransform*> Children;
		bool IsParented;

	public:
		CTransform();
		void SetParent(CTransform* parent);
		void Tick(float dt) override;
	};

	class EEntity : public NObject
	{
	public:
		class CTransform* Transform;

	protected:
		NWorld* m_World;
		vector<CComponent*> m_Components;
		bool m_Initialized;
		friend class NWorld;

	public:
		EEntity();
		~EEntity();

		inline NWorld* GetWorld() { return m_World; }
		inline void SetWorld(NWorld* world) { m_World = world; }

		// Create and add component of type
		template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
		T* AddComponent()
		{
			T* comp = new T();
			comp->m_Owner = this;
			m_Components.push_back(comp);
			return comp;
		}

		template<typename T>
		T* GetComponent()
		{
			for (CComponent* comp : m_Components)
			{
				if (typeid(*comp).name() == typeid(T).name())
				{
					return (T*)comp;
				}
				//if (comp->GetTypeID() == T::TypeID)
				//{
				//	return (T*)comp;
				//}
			}
			return nullptr;
		}

		vector<CComponent*> GetAllComponents()
		{
			return m_Components;
		}

		virtual void OnEnable() {};
		virtual void Begin() {};
		virtual void Tick(float dt) {};
		virtual void OnDisable() {};
	};

	// behaviour in level lifetime
	class GGameMode
	{
	protected:
		NWorld* m_World;
		friend class NWorld;

	public:
		GGameMode();

		inline NWorld* GetWorld() { return m_World; }
		inline void SetWorld(NWorld* world) { m_World = world; }

		virtual void Awake() {};
		virtual void Begin() {};
		virtual void Tick(float dt) {};
	};

	// behaviour in application lifetime
	class NGameInstance
	{
	public:
		virtual void Begin() {};
		virtual void Tick(float dt) {};
	};

	// space where entities are inserted in
	class NWorld
	{
	protected:
		GGameMode* m_GameMode;
		vector<EEntity*> m_Entities;
		queue<EEntity*> m_NextFrame;

	public:
		NWorld();

		void Destroy(EEntity* entity);
		void Awake();
		void Begin();
		void Tick(float dt);

		inline vector<EEntity*> GetAllEntities() { return m_Entities; }
		void SetGameMode(GGameMode* gameMode);

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate()
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = vec3(0.f);
			m_Entities.push_back(entity);
			m_NextFrame.push(entity);
			entity->OnEnable();
			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate(vec3 position)
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = position;
			entity->Transform->Rotation = vec3(0.f);
			m_Entities.push_back(entity);
			m_NextFrame.push(entity);
			entity->OnEnable();
			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate(vec3 position, vec3 rotation)
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = position;
			entity->Transform->Rotation = rotation;
			m_Entities.push_back(entity);
			m_NextFrame.push(entity);
			entity->OnEnable();
			return entity;
		}
	};
} 