#pragma once
#include "nata.h"
#include "collisionutils.h"

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

	public:
		static unsigned int SphereID;
		static unsigned int BoxID;

	public:
		CCollider();
	};
}