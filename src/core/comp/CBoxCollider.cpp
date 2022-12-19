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
	}

	void CBoxCollider::Begin()
	{
		SuperBegin();
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
		int intersectCount = 0;
		for (CBoxCollider* collider : boxColliders)
		{
			if (collider == this)
			{
				continue;
			}
			if (Intersect(m_Box, collider->GetBox()))
			{
				intersectCount++;
			}
		}

		if (intersectCount > 0)
		{
			Handles::DrawWireCube(Position, Bounds, vec3(0.f, 1.f, 0.f));
		}
		else
		{
			Handles::DrawWireCube(Position, Bounds, vec3(1.f, 0.f, 0.f));
		}
	}
}