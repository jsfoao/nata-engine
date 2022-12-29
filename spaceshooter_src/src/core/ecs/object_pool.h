#pragma once
#include "core/core.h"
#include "core/ecs/ecs.h"

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
		unsigned int Size;
		std::vector<FObject<T>*> m_Objects;
		FObject<T>* m_CurrentObj;
	public:
		NObjectPool(unsigned int size)
		{
			unsigned int id = 0;
			Size = size;
			m_Objects.reserve(Size);
			for (unsigned int i = 0; i < Size; i++)
			{
				FObject<T>* obj = new FObject<T>();
				m_Objects.push_back(obj);
			}

			for (unsigned int i = 0; i < Size - 1; i++)
			{
				T* entity = Instantiate<T>(NEngine::World, false);
				m_Objects[i]->Object = entity;
				m_Objects[i]->Next = m_Objects[i + 1];
			}
			T* entity = Instantiate<T>(NEngine::World, false);
			m_Objects[Size - 1]->Object = entity;
			m_Objects[Size - 1]->Next = nullptr;

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
			for (unsigned int i = 0; i < Size; i++)
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