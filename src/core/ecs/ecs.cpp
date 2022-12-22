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

	void NWorld::Destroy(EEntity* entity)
	{
		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i] == entity)
			{
				m_Entities.erase(m_Entities.begin() + i);
				delete entity;
				return;
			}
		}
		std::cout << "WARNING::DESTROY: OBJECT IS NOT INSTANTIATED" << std::endl;
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
		while (!m_NextFrame.empty())
		{
			m_NextFrame.front()->Begin();
			m_NextFrame.pop();
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
}