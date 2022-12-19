#include "CCollider.h"

namespace Nata
{
	INIT_COMPONENT(CCollider);

	CCollider::CCollider() : CComponent()
	{
		INIT_ID(CCollider);
		Position = vec3(0.f);
		LockOwner = true;
	}
}