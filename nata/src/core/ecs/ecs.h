#pragma once
#include <vector>
#include <queue>
#include "nata_math.h"
#include <iostream>
#include <string>

using namespace std;

#define SELF \
    static auto helper() -> std::remove_reference<decltype(*this)>::type; \
    typedef decltype(helper()) self

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
		std::string Name;

	protected:
		unsigned int m_ID;

	public:
		NObject();
		inline unsigned int GetID() { return m_ID; }
	};

	// Entity components
	class CComponent : public NObject
	{
	protected:
		EEntity* m_Owner;
		bool m_Enabled;
		unsigned int m_TypeID = 0;

		friend class EEntity;
		friend class NWorld;

	public:
		CComponent();
		CComponent(EEntity* owner);

		void SetEnable(bool enable);
		inline unsigned int GetTypeID() { return m_TypeID; }
		inline EEntity* GetOwner() { return m_Owner; }
		inline void SetOwner(EEntity* owner) { m_Owner = owner; }
		inline bool IsEnable() { return m_Enabled; }

		virtual void Begin() {};
		virtual void Tick(float dt) {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};
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
		vector<CComponent*> m_EnabledComponents;
		bool m_Enabled;
		bool m_Destroyed;
		friend class NWorld;

	public:
		EEntity();
		~EEntity();

		inline NWorld* GetWorld() { return m_World; }
		inline void SetWorld(NWorld* world) { m_World = world; }
		void SetEnable(bool enable);

		// Create and add component of type
		template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
		T* AddComponent()
		{
			T* comp = new T();
			comp->m_Owner = this;
			comp->m_Enabled = m_Enabled;
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
		virtual void OnDestroy() {};
	};

	// behaviour in level lifetime
	class GGameMode : public NObject
	{
	protected:
		NWorld* m_World;
		friend class NWorld;

	public:
		GGameMode();

		template<typename T, class = typename std::enable_if<std::is_base_of<GGameMode, T>::value>::type>
		static T* Init()
		{
			T* gameMode = new T();
			return gameMode;
		}

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
	class NWorld : public NObject
	{
	protected:
		GGameMode* m_GameMode;
		// All entities in world, both enabled and disabled
		vector<EEntity*> m_Entities;
		// Only enabled entities in world
		vector<EEntity*> m_Enabled;

		// Entities to enable/disable next frame
		queue<std::pair<EEntity*, bool>> m_EnableQueue;
		// Entities to begin next frame
		queue<EEntity*> m_BeginQueue;
		// Entities to destroy next frame
		queue<EEntity*> m_DestroyQueue;

		friend class EEntity;

	public:
		NWorld();

		void Destroy(EEntity* entity);
		void Awake();
		void Begin();
		void Tick(float dt);

		inline vector<EEntity*> GetAllEntities() { return m_Entities; }
		inline GGameMode* GetGameMode() { return m_GameMode; }
		void SetGameMode(GGameMode* gameMode);
		int GetEntityIndex(EEntity* entity);

		static NWorld* Init();
		static NWorld* Init(GGameMode* gameMode);

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate(bool enable = true)
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = vec3(0.f);
			entity->m_ID = m_Entities.size();
		
			m_Entities.push_back(entity);
			m_BeginQueue.push(entity);
		
			entity->SetEnable(enable);

			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate(vec3 position, bool enable = true)
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = position;
			entity->Transform->Rotation = vec3(0.f);
			entity->m_ID = m_Entities.size();
		
			m_Entities.push_back(entity);
			m_BeginQueue.push(entity);
		
			entity->SetEnable(enable);
			
			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		T* Instantiate(vec3 position, vec3 rotation, bool enable = true)
		{
			T* entity = new T();
			entity->m_World = this;
			entity->Transform->Position = position;
			entity->Transform->Rotation = rotation;

			entity->m_ID = m_Entities.size();
			m_Entities.push_back(entity);
			m_BeginQueue.push(entity);

			entity->SetEnable(enable);

			return entity;
		}
	};
} 