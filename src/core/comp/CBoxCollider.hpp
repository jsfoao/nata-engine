#pragma once
#include "nata.h"
#include "collisionutils.h"

namespace Nata
{
	class CBoxCollider: public CComponent
	{
	public:
		vec3 Position;
		vec3 Bounds;
		NBox Box;

	public:
		CBoxCollider() : CComponent()
		{
			Position = vec3(0.f);
			Bounds = vec3(3.f);
		}

		inline NBox GetBox()
		{
			return Box;
		}

		void Begin() override
		{
			SuperBegin();
			Position = GetOwner()->Transform->Position;
		}

		void Tick(float dt) override
		{
			//SuperTick(dt);
			//vec3 hBound = m_Bounds / 2.f;
			//m_Position = GetOwner()->Transform->Position;
			//m_Box = NBox(
			//	NRange(m_Position.x - hBound.x, m_Position.x + hBound.x),
			//	NRange(m_Position.y - hBound.y, m_Position.y + hBound.y),
			//	NRange(m_Position.z - hBound.z, m_Position.z + hBound.z)
			//);
			//NWorld* world = GetOwner()->GetWorld();
			//Handles::DrawWireCube(m_Position, m_Bounds, vec3(0.f, 1.f, 0.f));
			////std::vector<CBoxCollider*> cols = GetComponentsOfType<CBoxCollider>(world);

			////bool intersecting = false;
			////for (CBoxCollider* col : cols)
			////{
			////	if (col == this)
			////	{
			////		continue;
			////	}
			////	intersecting = Intersect(m_Box, col->GetBox());
			////}

			////if (intersecting)
			////{
			////}
			////else
			////{
			////	Handles::DrawWireCube(m_Position, m_Bounds, vec3(1.f, 0.f, 0.f));
			////}
		}
	};
}