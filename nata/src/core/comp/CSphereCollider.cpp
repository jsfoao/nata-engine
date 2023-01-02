#include "CSphereCollider.h"

namespace Nata
{
	INIT_COMPONENT(CSphereCollider);

	CSphereCollider::CSphereCollider() : CCollider()
	{
		Position = vec3(0.f);
		Radius = 1.f;
	}

	void CSphereCollider::Begin()
	{
	}

	void CSphereCollider::Tick(float dt)
	{
		SuperTick(dt);

		m_Sphere = NSphere(Position, Radius);

		std::vector<CSphereCollider*> sphereColliders = GetAllComponentsOfType<CSphereCollider>(GetOwner()->GetWorld());

		int intersectCount = 0;
		for (CSphereCollider* collider : sphereColliders)
		{
			if (collider == this)
			{
				continue;
			}
			if (Intersect(m_Sphere, collider->GetSphere()))
			{
				intersectCount++;
			}
		}

		if (intersectCount > 0)
		{
			Handles::DrawWireSphere(Position, Radius, vec3(0.f, 1.f, 0.f));
		}
		else
		{
			Handles::DrawWireSphere(Position, Radius, vec3(1.f, 0.f, 0.f));
		}
	}
}