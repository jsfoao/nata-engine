#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <tuple>
#include "nata_math.h"

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
	// Objects will get constructed in current active world
	class NObject
	{
		friend class NWorld;
		friend class EEntity;
		friend class CComponent;
		friend class GGameMode;

	public:
		std::string Name;

	protected:
		unsigned int m_ID;
		bool m_Began;
		bool m_Enabled;
		// TODO: implement destroyed logic
		bool m_Destroyed;
		NWorld* m_World;

	public:
		NObject();

		virtual void OnEnable() {};
		virtual void Awake() {};
		virtual void Begin() {};
		virtual void Tick(float dt) {};
		virtual void OnDisable() {};
		virtual void OnDestroy() {};
		
		virtual void Super_OnEnable() {};
		virtual void Super_Awake() {};
		virtual void Super_Begin() {};
		virtual void Super_Tick(float dt) {};
		virtual void Super_OnDisable() {};
		virtual void Super_OnDestroy() {};
	
		inline NWorld* GetWorld() { return m_World; }
		inline void SetWorld(NWorld* world) { m_World = world; }
		inline bool IsEnabled() { return m_Enabled; }

		// Enables object next frame
		void Super_SetEnable(bool enable);
		virtual void SetEnable(bool enable, bool thisFrame = false) {};
		virtual void Super_Destroy() {};

		inline unsigned int GetID() { return m_ID; }
	};

	// Entity components
	class CComponent : public NObject
	{
	protected:
		EEntity* m_Owner;
		bool m_PreEnable;

		friend class EEntity;
		friend class NWorld;

	public:
		CComponent();

		void Super_OnEnable() override;
		void Super_Awake() override;
		void Super_Begin() override;
		void Super_Tick(float dt) override;
		void Super_OnDisable() override;
		void Super_OnDestroy() override;

		inline EEntity* GetOwner() { return m_Owner; }
		inline void SetOwner(EEntity* owner) { m_Owner = owner; }
		inline bool IsPreEnabled() { return m_PreEnable; }
		void SetEnable(bool enable, bool thisFrame = false) override;
		void Super_Destroy() override;
	};

	class CTransform : public CComponent
	{
		GENERATE_COMPONENT;
	public:
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;
		vec3 LocalPosition;
		vec3 LocalRotation;
		vec3 LocalScale;

		vec3 Forward;
		vec3 Right;
		vec3 Up;
		
	protected:
		CTransform* m_Parent;
		vector<CTransform*> m_Children;
		bool m_IsParented;

	public:
		CTransform();

		void Tick(float dt) override;
		// Set parent to nullptr to remove parent
		void SetParent(CTransform* parent);
	};

	class CSpatialComponent : public CComponent
	{
	public:
		// Local transform
		CTransform* Transform;

		CSpatialComponent();
	};

	class EEntity : public NObject
	{
	public:
		class CTransform* Transform;

	protected:
		vector<CComponent*> m_Components;
		vector<CComponent*> m_EnabledComponents;
		bool m_Destroyed;
		friend class NWorld;
		friend class CComponent;

	public:
		EEntity();
		~EEntity();

		void Super_OnEnable() override;
		void Super_Awake() override;
		void Super_Begin() override;
		void Super_Tick(float dt) override;
		void Super_OnDisable() override;
		void Super_OnDestroy() override;

		inline NWorld* GetWorld() { return m_World; }
		inline void SetWorld(NWorld* world) { m_World = world; }
		void SetEnable(bool enable, bool thisFrame = false) override;
		void Super_Destroy() override;

		// Create and add component of type
		template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
		T* AddComponent(bool enable = true)
		{
			T* comp = new T();
			comp->m_Owner = this;
			comp->SetEnable(enable);
			comp->m_World = m_World;
			m_Components.push_back(comp);
			return comp;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<CComponent, T>::value>::type>
		T* GetComponent()
		{
			for (CComponent* comp : m_Components)
			{
				if (typeid(*comp).name() == typeid(T).name())
				{
					return (T*)comp;
				}
			}
			return nullptr;
		}

		vector<CComponent*> GetAllComponents()
		{
			return m_Components;
		}
	};

	// behaviour in level lifetime
	class GGameMode : public NObject
	{
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
	public:
		static NWorld* Current;

	protected:
		GGameMode* m_GameMode;
		// All entities in world, both enabled and disabled
		vector<EEntity*> m_Entities;
		// Only enabled entities in world
		vector<EEntity*> m_Enabled;

		// Objects to enable/disable next frame
		queue<std::tuple<NObject*, bool>> m_EnableQueue;
		// Objects to begin next frame
		queue<NObject*> m_BeginQueue;
		// Objects to destroy next frame
		queue<NObject*> m_DestroyQueue;

		friend class EEntity;
		friend class CComponent;
		friend class NObject;

	public:
		NWorld();

		static NWorld* Init();
		static NWorld* Init(GGameMode* gameMode);

		void Awake() override;
		void Begin() override;
		void Tick(float dt) override;

		inline vector<EEntity*> GetAllEntities() { return m_Entities; }
		inline vector<EEntity*> GetAllEnabledEntities() { return m_Enabled; }
		inline GGameMode* GetGameMode() { return m_GameMode; }
		void SetGameMode(GGameMode* gameMode);
		int GetEntityIndex(EEntity* entity);

		void Destroy(NObject* object);
		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		static T* Instantiate(bool enable = true)
		{
			T* entity = new T();
			entity->SetEnable(enable);
			entity->m_ID = NWorld::Current->m_Entities.size();

			NWorld::Current->m_Entities.push_back(entity);

			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		static T* Instantiate(vec3 position, bool enable = true)
		{
			T* entity = new T();
			entity->SetEnable(enable);
			entity->Transform->Position = position;
			entity->Transform->Rotation = vec3(0.f);
			entity->m_ID = NWorld::Current->m_Entities.size();
		
			NWorld::Current->m_Entities.push_back(entity);
			
			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		static T* Instantiate(vec3 position, vec3 rotation, bool enable = true)
		{
			T* entity = new T();
			entity->SetEnable(enable);
			entity->Transform->Position = position;
			entity->Transform->Rotation = rotation;
			entity->m_ID = NWorld::Current->m_Entities.size();
			
			m_Entities.push_back(entity);

			return entity;
		}

		template<typename T, class = typename std::enable_if<std::is_base_of<EEntity, T>::value>::type>
		static T* Instantiate(vec3 position, vec3 rotation, vec3 scale, bool enable = true)
		{
			T* entity = new T();
			entity->SetEnable(enable);
			entity->Transform->Position = position;
			entity->Transform->Rotation = rotation;
			entity->Transform->Scale = scale;
			entity->m_ID = NWorld::Current->m_Entities.size();
			
			NWorld::Current->m_Entities.push_back(entity);

			return entity;
		}
	};
} 