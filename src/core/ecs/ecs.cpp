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
	}

	EEntity::~EEntity()
	{
		for (CComponent* component : m_Components)
		{
			delete component;
		}
	}

	NGameMode::NGameMode()
	{
		m_World = nullptr;
	}

	NWorld::NWorld()
	{
		m_GameMode = nullptr;
	}

	void NWorld::SetGameMode(NGameMode* gameMode)
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
				return;
			}
		}
		std::cout << "WARNING::DESTROY: OBJECT IS NOT INSTANTIATED" << std::endl;
	}

	void NWorld::Begin()
	{
		m_GameMode->Begin();
		for (EEntity* entity : m_Entities)
		{
			entity->Begin();
			for (CComponent* comp : entity->m_Components)
			{
				comp->Begin();
			}
		}
	}

	void NWorld::Tick(float dt)
	{
		m_GameMode->Tick(dt);
		for (EEntity* entity : m_Entities)
		{
			entity->Tick(dt);
			for (CComponent* comp : entity->m_Components)
			{
				comp->Tick(dt);
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
		Right.x = cos(radians(Rotation.y)) * cos(radians(Rotation.x));
		Right.y = sin(radians(Rotation.x));
		Right.z = sin(radians(Rotation.y)) * cos(radians(Rotation.x));
		Right = normalize(Right);
		Forward = -normalize(cross(vec3(0.f, 1.f, 0.f), Right));
		Up = cross(Right, -Forward);

		if (IsParented)
		{
			Position = Parent->Position + LocalPosition;
		}
	}

	unsigned int CTransform::TypeID = 0;
}