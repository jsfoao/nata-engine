#include "CBoxCollider.h"

namespace Nata
{
	INIT_COMPONENT(CBoxCollider);

	CBoxCollider::CBoxCollider() : CCollider()
	{
		Name = "BoxCollider";
		LockPosition = true;
		LockRotation = true;
		LockScale = true;
		AddOnCollisionCallback(OnCollision);
		AddOnCollisionEnterCallback(OnCollisionEnter);
		AddOnCollisionExitCallback(OnCollisionExit);
	}

	void CBoxCollider::OnEnable()
	{
	}

	void CBoxCollider::Begin()
	{
		vec3 position = Transform->Position;
		vec3 rotation = Transform->Rotation;
		vec3 scale = Transform->Scale;

		vec3 hBound = scale / 2.f;
		m_Box = NBox(
			NRange(position.x - hBound.x, position.x + hBound.x),
			NRange(position.y - hBound.y, position.y + hBound.y),
			NRange(position.z - hBound.z, position.z + hBound.z)
		);
	}

	void CBoxCollider::Tick(float dt)
	{
		vec3 position = Transform->Position;
		vec3 rotation = Transform->Rotation;
		vec3 scale = Transform->Scale;

		vec3 hBound = scale / 2.f;
		m_Box = NBox(
			NRange(position.x - hBound.x, position.x + hBound.x),
			NRange(position.y - hBound.y, position.y + hBound.y),
			NRange(position.z - hBound.z, position.z + hBound.z)
		);

		std::vector<CBoxCollider*> boxColliders = GetAllComponentsOfType<CBoxCollider>(NEngine::World);
		for (CBoxCollider* collider : boxColliders)
		{
			if (collider == this || collider->m_Enabled == false)
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
			Handles::DrawWireCube(position, rotation, scale, vec3(1.f, 0.f, 0.f));
		}
	}

	void CBoxCollider::OnDisable()
	{
		for (auto& col : m_Overlaps)
		{
			col->m_Overlaps.clear();
			col->CallOnCollisionExitCallback(col, this);
		}
		m_Overlaps.clear();
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