#pragma once
#include "core.h"
#include "ecs/ecs.h"

namespace Nata
{
	class EEntity;
	template<typename T>
	struct FObject
	{
		T* Object;
		FObject* Next;

		FObject()
		{
			Object = nullptr;
			Next = nullptr;
		}

		FObject(T* obj)
		{
			Object = obj;
			Next = nullptr;
		}

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
		static const int PoolSize = 100;
		FObject<T>* m_Objects[PoolSize];
		FObject<T>* m_CurrentObj;
	public:
		NObjectPool()
		{
			for (unsigned int i = 0; i < PoolSize; i++)
			{
				FObject<T>* obj = new FObject<T>();
				m_Objects[i] = obj;
			}

			for (unsigned int i = 0; i < PoolSize - 1; i++)
			{
				T* entity = Instantiate<T>(NEngine::World);
				entity->SetEnable(false);
				m_Objects[i]->Object = entity;
				m_Objects[i]->Next = m_Objects[i + 1];
			}
			T* entity = Instantiate<T>(NEngine::World);
			entity->SetEnable(false);
			m_Objects[PoolSize - 1]->Object = entity;
			m_Objects[PoolSize - 1]->Next = nullptr;

			m_CurrentObj = m_Objects[0];
		}

		T* Create(vec3 position)
		{
			if (m_CurrentObj == nullptr)
			{
				std::cout << "OBJECTPOOL::CREATE : Maxed out pool" << std::endl;
				return nullptr;
			}
			FObject<T>* temp = m_CurrentObj;
			temp->Object->Transform->Position = position;
			temp->Object->SetEnable(true);
			m_CurrentObj = m_CurrentObj->Next;
			return temp->Object;
		}

		void Delete(EEntity* entity)
		{
			for (unsigned int i = 0; i < PoolSize; i++)
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