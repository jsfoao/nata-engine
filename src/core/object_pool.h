#pragma once
#include "core.h"
#include "ecs/ecs.h"

namespace Nata
{
#define POOL_SIZE 100

	class EEntity;
	template<typename T>
	struct FObject
	{
		T* Object;
		FObject* Next;

		FObject(T* obj, FObject* next)
		{
			Object = obj;
			Next = next;
		}
	};

	template<typename T>
	class NObjectPool
	{
	protected:
		FObject<T>* m_Objects[POOL_SIZE];
		FObject<T>* m_CurrentObj;

	public:
		NObjectPool()
		{
			for (unsigned int i = 0; i < POOL_SIZE - 1; i++)
			{
				T* entity = Instantiate<T>(NEngine::World);
				entity->SetEnable(false);
				FObject<T>* obj = new FObject(entity, m_Objects[i + 1]);
				m_Objects[i] = obj;
			}
			m_Objects[POOL_SIZE - 1]->Next = nullptr;
			m_CurrentObj = m_Objects[0];
		}

		T* Create(vec3 position)
		{
			if (m_CurrentObj == nullptr)
			{
				return nullptr;
			}
			m_CurrentObj->Object->Transform->Position = position;
			m_CurrentObj->Object->SetEnable(true);
			m_CurrentObj = m_CurrentObj->Next;
			return m_CurrentObj->Object;
		}

		void Delete(EEntity* entity)
		{
			for (unsigned int i = 0; i < POOL_SIZE; i++)
			{
				if (entity == m_Objects[i]->Object)
				{
					m_Objects[i]->Object->SetEnable(false);
					m_CurrentObj = m_Objects[i];
					return;
				}
			}
		}
	};
}