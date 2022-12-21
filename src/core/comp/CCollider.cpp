#include "CCollider.h"

namespace Nata
{
	INIT_COMPONENT(CCollider);

	CCollider::CCollider() : CComponent()
	{
		INIT_ID(CCollider);
		Position = vec3(0.f);
		LockOwner = true;
		HandlesColor = vec3(1.f, 0.f, 0.f);
		DrawHandles = true;
	}

	void CCollider::CallOnCollisionCallback(CCollider* owner, CCollider* other)
	{
		for (auto& f : m_OnCollisionCallbacks)
		{
			f(owner, other);
		}
	}

	void CCollider::CallOnCollisionEnterCallback(CCollider* owner, CCollider* other)
	{
		for (auto& f : m_OnCollisionEnterCallbacks)
		{
			f(owner, other);
		}
	}

	void CCollider::CallOnCollisionExitCallback(CCollider* owner, CCollider* other)
	{
		for (auto& f : m_OnCollisionExitCallbacks)
		{
			f(owner, other);
		}
	}

	void CCollider::RemoveOverlap(CCollider* collider)
	{
		for (unsigned int i = 0; i < m_Overlaps.size(); i++)
		{
			if (collider == m_Overlaps[i])
			{
				m_Overlaps.erase(m_Overlaps.begin() + i);
			}
		}
	}

	bool CCollider::IsOverlapping(CCollider* collider)
	{
		for (auto& overlap : m_Overlaps)
		{
			if (collider == overlap)
			{
				return true;
			}
		}
		return false;
	}
}