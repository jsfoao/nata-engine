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

	void CComponent::SuperBegin()
	{
		if (!m_Enabled)
		{
			return;
		}
	}

	void CComponent::SuperTick(float dt)
	{
		if (!m_Enabled)
		{
			return;
		}
	}

	EEntity::EEntity()
	{
		Transform = AddComponent<CTransform>();
		m_World = nullptr;
		m_Initialized = false;
		m_Destroyed = false;
	}

	EEntity::~EEntity()
	{
		for (CComponent* component : m_Components)
		{
			delete component;
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
		m_Destroy.push(entity);
		entity->m_Destroyed = true;
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
		// Begin entities on queue from previous frame
		while (!m_Begin.empty())
		{
			// Dont begin destroyed entities
			if (m_Begin.front()->m_Destroyed)
			{
				continue;
			}
			m_Begin.front()->Begin();
			m_Begin.pop();
		}

		// Destroy entities on queue from previous frame
		while (!m_Destroy.empty())
		{
			int index = GetEntityIndex(m_Destroy.front());
			if (index == -1)
			{
				delete m_Destroy.front();
				m_Destroy.pop();
				continue;
			}
			m_Entities.erase(m_Entities.begin() + index);
			m_Destroy.pop();
		}

		m_GameMode->Tick(dt);
		for (int e = m_Entities.size() - 1; e >= 0; e--)
		{
			EEntity* entity = m_Entities[e];
			entity->Tick(dt);
			for (int c = entity->m_Components.size() - 1; c >= 0; c--)
			{
				CComponent* component = m_Entities[e]->m_Components[c];
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