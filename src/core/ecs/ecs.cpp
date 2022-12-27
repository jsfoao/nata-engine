#include "ecs.h"
namespace Nata
{
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

	void CComponent::SetEnable(bool enable)
	{
		m_Enabled = enable;
		if (enable == true)
		{
			OnEnable();
		}
		if (enable == false)
		{
			OnDisable();
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

	void EEntity::SetEnable(bool enable)
	{
		std::pair<EEntity*, bool> enabledState;
		enabledState.first = this;
		enabledState.second = enable;
		GetWorld()->m_EnableQueue.push(enabledState);

		for (auto& comp : m_Components)
		{
			comp->m_Enabled = enable;
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

	void NWorld::Destroy(EEntity* entity)
	{
		m_DestroyQueue.push(entity);
		entity->m_Destroyed = true;
		entity->OnDestroy();
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
		// Enable entities on queue from previous frame
		while (!m_EnableQueue.empty())
		{
			EEntity* entity = m_EnableQueue.front().first;
			bool enabled = m_EnableQueue.front().second;
			entity->m_Enabled = enabled;

			if (entity->m_Enabled == true)
			{
				m_Enabled.push_back(entity);
			}
			else
			{
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
			// Dont begin destroyed entities
			if (m_BeginQueue.front()->m_Destroyed)
			{
				continue;
			}
			m_BeginQueue.front()->Begin();
			m_BeginQueue.pop();
		}

		// Destroy entities on queue from previous frame
		while (!m_DestroyQueue.empty())
		{
			int index = GetEntityIndex(m_DestroyQueue.front());
			if (index == -1)
			{
				m_DestroyQueue.pop();
				continue;
			}
			m_Entities.erase(m_Entities.begin() + index);
			m_DestroyQueue.pop();
		}

		m_GameMode->Tick(dt);
		// Only tick on enabled entities
		for (int e = m_Enabled.size() - 1; e >= 0; e--)
		{
			EEntity* entity = m_Enabled[e];
			entity->Tick(dt);

			for (int c = entity->m_Components.size() - 1; c >= 0; c--)
			{
				CComponent* component = m_Enabled[e]->m_Components[c];
				if (component->m_Enabled)
					component->Tick(dt);
			}
		}
	}

	CTransform::CTransform()
	{
		m_TypeID = 0;
		Position = vec3(0.f);
		Scale = vec3(1.f, 1.f, 1.f);
		Rotation = vec3(0.f);
		LocalPosition = vec3(0.f);
		Forward = vec3(0.f);
		Right = vec3(0.f);
		Up = vec3(0.f);
		Parent = nullptr;
		IsParented = false;
	}

	void CTransform::SetParent(CTransform* parent)
	{
		if (parent == nullptr)
		{
			std::cout << "WARNING::CTRANSFORM : INVALID PARENT" << std::endl;
			return;
		}
		IsParented = true;
		Parent = parent;
		LocalPosition = parent->Position - Position;
		parent->Children.push_back(this);
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

		if (IsParented)
		{
			Position = Parent->Position + LocalPosition;
		}
	}

	unsigned int CTransform::TypeID = 0;
	NObject::NObject()
	{
		Name = "";
		m_ID = 0;
	}
}