#pragma once
#include "nata.h"
#include "collisionutils.h"
#include <functional>

namespace Nata
{
	class CBoxCollider;
	class CSphereCollider;
	class CCollider : public CComponent
	{
		GENERATE_COMPONENT;

	public:
		vec3 Position;
		// sets position to be the same as the owner
		bool LockOwner;
		vec3 HandlesColor;
		bool DrawHandles;

	protected:
		std::vector<void(*)(CCollider*, CCollider*)> m_OnCollisionCallbacks;
		std::vector<void(*)(CCollider*, CCollider*)> m_OnCollisionEnterCallbacks;
		std::vector<void(*)(CCollider*, CCollider*)> m_OnCollisionExitCallbacks;

	public:
		static unsigned int SphereID;
		static unsigned int BoxID;
		std::vector<CCollider*> m_Overlaps;

	public:
		CCollider();

		inline void AddOnCollisionCallback(void(*ptr)(CCollider*, CCollider*))
		{
			m_OnCollisionCallbacks.push_back(ptr);
		}

		inline void AddOnCollisionEnterCallback(void(*ptr)(CCollider*, CCollider*))
		{
			m_OnCollisionEnterCallbacks.push_back(ptr);
		}

		inline void AddOnCollisionExitCallback(void(*ptr)(CCollider*, CCollider*))
		{
			m_OnCollisionExitCallbacks.push_back(ptr);
		}

		inline std::vector<CCollider*> GetOverlaps()
		{
			return m_Overlaps;
		}

		inline unsigned int GetOverlapsSize()
		{
			return m_Overlaps.size();
		}

		inline void AddOverlap(CCollider* collider)
		{
			m_Overlaps.push_back(collider);
		}

		void CallOnCollisionCallback(CCollider* owner, CCollider* other);
		void CallOnCollisionEnterCallback(CCollider* owner, CCollider* other);
		void CallOnCollisionExitCallback(CCollider* owner, CCollider* other);
		void RemoveOverlap(CCollider* collider);
		bool IsOverlapping(CCollider* collider);
	};
}