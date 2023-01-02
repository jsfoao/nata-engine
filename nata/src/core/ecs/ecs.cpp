#include "ecs.h"
namespace Nata
{
	unsigned int CTransform::TypeID = 0;
	NObject::NObject()
	{
		Name = "Object";
		m_ID = 0;
		m_Began = false;
		m_Enabled = false;
		m_Destroyed = false;
	}

	void NObject::Super_SetEnable(bool enable)
	{
		std::tuple<NObject*, bool> enabledState;
		std::get<0>(enabledState) = this;
		std::get<1>(enabledState) = enable;
		GetWorld()->m_EnableQueue.push(enabledState);
	}

	CComponent::CComponent()
	{
		m_Owner = nullptr;
		m_Enabled = true;
	}

	CComponent::CComponent(EEntity* owner)
	{
		m_Owner = owner;
		m_Enabled = true;
	}

	void CComponent::Super_OnEnable()
	{
		OnEnable();
	}

	void CComponent::Super_Awake()
	{
		Awake();
	}

	void CComponent::Super_Begin()
	{
		Begin();
	}

	void CComponent::Super_Tick(float dt)
	{
		Tick(dt);
	}

	void CComponent::Super_OnDisable()
	{
		OnDisable();
	}

	void CComponent::Super_OnDestroy()
	{
		OnDestroy();
	}

	void CComponent::SetEnable(bool enable)
	{
		m_PreEnable = enable;

		// Object is already enabled
		if (enable == m_Enabled)
			return;

		Super_SetEnable(enable);
		EEntity* owner = GetOwner();
		if (owner != nullptr)
		{
			if (!owner->m_Enabled)
			{
				return;
			}
		}
		if (!m_Began)
		{
			m_Began = true;
			m_World->m_BeginQueue.push(this);
		}
	}

	void CComponent::Super_Destroy()
	{
		for (unsigned int i = 0; i < GetOwner()->m_Components.size(); i++)
		{
			if (this == GetOwner()->m_Components[i])
			{
				GetOwner()->m_Components.erase(GetOwner()->m_Components.begin() + i);
			}
		}
	}

	EEntity::EEntity()
	{
		Transform = AddComponent<CTransform>();
		m_World = nullptr;
		m_Enabled = false;
		m_Destroyed = false;
	}

	EEntity::~EEntity()
	{
		for (CComponent* component : m_Components)
		{
			delete component;
		}
	}

	void EEntity::Super_OnEnable()
	{
		m_World->m_Enabled.push_back(this);
		OnEnable();
	}

	void EEntity::Super_Awake()
	{
		Awake();
	}

	void EEntity::Super_Begin()
	{
		Begin();
	}

	void EEntity::Super_Tick(float dt)
	{
		Tick(dt);
	}

	void EEntity::Super_OnDisable()
	{
		OnDisable();
	}

	void EEntity::Super_OnDestroy()
	{
		OnDestroy();
	}

	void EEntity::SetEnable(bool enable)
	{
		// Object is already enabled
		if (enable == m_Enabled)
			return;

		Super_SetEnable(enable);
		if (!m_Began)
		{
			m_Began = true;
			m_World->m_BeginQueue.push(this);
		}
	}

	void EEntity::Super_Destroy()
	{
		for (unsigned int i = 0; i < m_World->m_Entities.size(); i++)
		{
			if (this == m_World->m_Entities[i])
			{
				m_World->m_Entities.erase(m_World->m_Entities.begin() + i);
				return;
			}
		}
	}

	GGameMode::GGameMode()
	{
		m_World = nullptr;
	}

	NWorld::NWorld()
	{
		m_GameMode = nullptr;
	}

	void NWorld::SetGameMode(GGameMode* gameMode)
	{
		gameMode->m_World = this;
		m_GameMode = gameMode;
	}

	int NWorld::GetEntityIndex(EEntity* entity)
	{
		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			if (entity == m_Entities[i])
			{
				return i;
			}
		}
		return -1;
	}

	NWorld* NWorld::Init()
	{
		NWorld* world = new NWorld();
		world->m_GameMode = nullptr;
		return world;
	}

	NWorld* NWorld::Init(GGameMode* gameMode)
	{
		NWorld* world = new NWorld();
		gameMode->m_World = world;
		world->m_GameMode = gameMode;
		return world;
	}

	void NWorld::Destroy(NObject* object)
	{
		// Object is already destroyed
		if (object->m_Destroyed)
		{
			return;
		}
		m_DestroyQueue.push(object);
		object->m_Destroyed = true;
		object->Super_OnDestroy();
	}

	void NWorld::Awake()
	{
		m_GameMode->Awake();
	}

	void NWorld::Begin()
	{
		m_GameMode->Begin();
	}

	void NWorld::Tick(float dt)
	{
		// Enabled or disable entities and components
		while (!m_EnableQueue.empty())
		{
			NObject* object = std::get<0>(m_EnableQueue.front());
			bool enabled = std::get<1>(m_EnableQueue.front());
			object->m_Enabled = enabled;

			// Enable entities on queue from previous frame
			if (object->m_Enabled == true)
			{
				object->Super_OnEnable();
			}
			else
			{
				object->Super_OnDisable();
				EEntity* entity = dynamic_cast<EEntity*>(object);
				if (entity == nullptr)
					continue;

				for (unsigned int i = 0; i < m_Enabled.size(); i++)
				{
					if (entity == m_Enabled[i])
					{
						m_Enabled.erase(m_Enabled.begin() + i);
					}
				}
			}
			m_EnableQueue.pop();
		}

		// Begin entities on queue from previous frame
		while (!m_BeginQueue.empty())
		{
			NObject* object= m_BeginQueue.front();
			// Dont begin destroyed entities
			if (object->m_Destroyed)
			{
				continue;
			}
			object->Super_Begin();
			m_BeginQueue.pop();
		}

		// Destroy entities on queue from previous frame
		while (!m_DestroyQueue.empty())
		{
			NObject* object = m_DestroyQueue.front();
			object->Super_Destroy();
			m_DestroyQueue.pop();
		}

		m_GameMode->Tick(dt);
		// Only tick on enabled entities
		for (int e = m_Enabled.size() - 1; e >= 0; e--)
		{
			EEntity* entity = m_Enabled[e];
			entity->Super_Tick(dt);

			for (int c = entity->m_Components.size() - 1; c >= 0; c--)
			{
				CComponent* component = m_Enabled[e]->m_Components[c];
				if (component->m_Enabled)
					component->Super_Tick(dt);
			}
		}
	}

	CTransform::CTransform()
	{
		Name = "Transform";
		Position = vec3(0.f);
		Scale = vec3(1.f, 1.f, 1.f);
		Rotation = vec3(0.f);
		LocalPosition = vec3(0.f);
		LocalRotation = vec3(0.f);
		LocalScale = vec3(1.f);
		Forward = vec3(0.f);
		Right = vec3(0.f);
		Up = vec3(0.f);
		m_Parent = nullptr;
		m_IsParented = false;
	}

	void CTransform::SetParent(CTransform* parent)
	{
		if (parent == nullptr)
		{
			LocalPosition = vec3(0.f);
			LocalRotation = vec3(0.f);
			LocalScale = vec3(1.f);
			if (!m_IsParented)
			{
				return;
			}
			// Remove itself from parent's children
			for (unsigned int i = 0; i < m_Parent->m_Children.size(); i++)
			{
				if (m_Parent->m_Children[i] == this)
				{
					m_Parent->m_Children.erase(m_Parent->m_Children.begin() + i);
					break;
				}
			}
			m_IsParented = false;
			m_Parent = nullptr;
			return;
		}
		m_IsParented = true;
		m_Parent = parent;
		Position = m_Parent->Position + LocalPosition;
		Rotation = m_Parent->Rotation + LocalRotation;
		Scale = m_Parent->Scale + LocalScale - vec3(1.f);
		parent->m_Children.push_back(this);
	}

	void CTransform::Tick(float dt)
	{
		mat4 model = mat4(1.f);
		model = rotate(model, radians(Rotation.x), vec3(-1.f, 0.f, 0.f));
		model = rotate(model, radians(Rotation.y), vec3(0.f, -1.f, 0.f));
		model = rotate(model, radians(Rotation.z), vec3(0.f, 0.f, 1.f));
		Forward = vec4(0.f, 0.f, 1.f, 0.f) * model;
		Right = vec4(1.f, 0.f, 0.f, 0.f) * model;
		Right = normalize(Right); 
		Forward = normalize(Forward);
		Up = -cross(Right, Forward);

		if (m_IsParented)
		{
			Position = m_Parent->Position + LocalPosition;
			Rotation = m_Parent->Rotation + LocalRotation;
			Scale = m_Parent->Scale + LocalScale - vec3(1.f);
		}
	}

	CSpatialComponent::CSpatialComponent() : CComponent()
	{
		Transform = new CTransform();
	}
}