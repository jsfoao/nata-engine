#include "CBoxCollider.h"

namespace Nata
{
	INIT_COMPONENT(CBoxCollider);

	CBoxCollider::CBoxCollider() : CCollider()
	{
		INIT_ID(CBoxCollider);
		Position = vec3(0.f);
		Bounds = vec3(1.f);
		LockOwner = true;
		AddOnCollisionCallback(OnCollision);
		AddOnCollisionEnterCallback(OnCollisionEnter);
		AddOnCollisionExitCallback(OnCollisionExit);
	}

	void CBoxCollider::Begin()
	{
		if (LockOwner)
		{
			Position = GetOwner()->Transform->Position;
		}

		vec3 hBound = Bounds / 2.f;
		m_Box = NBox(
			NRange(Position.x - hBound.x, Position.x + hBound.x),
			NRange(Position.y - hBound.y, Position.y + hBound.y),
			NRange(Position.z - hBound.z, Position.z + hBound.z)
		);
	}

	void CBoxCollider::Tick(float dt)
	{
		if (LockOwner)
		{
			Position = GetOwner()->Transform->Position;
		}

		vec3 hBound = Bounds / 2.f;
		m_Box = NBox(
			NRange(Position.x - hBound.x, Position.x + hBound.x),
			NRange(Position.y - hBound.y, Position.y + hBound.y),
			NRange(Position.z - hBound.z, Position.z + hBound.z)
		);

		std::vector<CBoxCollider*> boxColliders = GetAllComponentsOfType<CBoxCollider>(GetOwner()->GetWorld());
		for (CBoxCollider* collider : boxColliders)
		{
			if (collider == this)
			{
				continue;
			}
			if (Intersect(m_Box, collider->GetBox()))
			{
				if (!IsOverlapping(collider))
				{
					// called on overlap enter
					AddOverlap(collider);
					CallOnCollisionEnterCallback(this, collider);
				}
				// called while overlapping
				CallOnCollisionCallback(this, collider);
			}
			else
			{
				if (IsOverlapping(collider))
				{
					// called on overlap exit
					RemoveOverlap(collider);
					CallOnCollisionExitCallback(this, collider);
				}
			}
		}

		if (DrawHandles)
		{
			Handles::DrawWireCube(Position, Bounds, HandlesColor);
		}
	}

	void CBoxCollider::OnCollision(CCollider* owner, CCollider* other)
	{
	}

	void CBoxCollider::OnCollisionEnter(CCollider* owner, CCollider* other)
	{
		owner->HandlesColor = vec3(0.f, 1.f, 0.f);
	}

	void CBoxCollider::OnCollisionExit(CCollider* owner, CCollider* other)
	{
		if (owner->GetOverlapsSize() == 0)
		{
			owner->HandlesColor = vec3(1.f, 0.f, 0.f);
		}
	}
}