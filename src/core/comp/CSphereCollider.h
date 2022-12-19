#pragma once
#include "nata.h"
#include "collisionutils.h"
#include "CCollider.h"

namespace Nata
{
	class CBoxCollider;
	class CSphereCollider : public CCollider
	{
		GENERATE_COMPONENT;

	public:
		vec3 Position;
		float Radius;

	protected:
		NSphere m_Sphere;

	public:
		CSphereCollider();
		inline NSphere GetSphere() { return m_Sphere; }
		void Begin() override;
		void Tick(float dt) override;
	};
}