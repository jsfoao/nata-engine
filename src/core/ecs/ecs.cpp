#include "ecs.h"
namespace Nata
{
	INIT_COMPONENT(CTransform)

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
}