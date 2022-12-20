#pragma once
#include "nata.h"
#include "collisionutils.h"
#include "CCollider.h"

namespace Nata
{
	class CSphereCollider;
	class CBoxCollider: public CCollider
	{
		GENERATE_COMPONENT;

	public:
		vec3 Position;
		vec3 Bounds;
		
	protected:
		NBox m_Box;

	public:
		CBoxCollider();
		inline NBox GetBox() { return m_Box; }
		void Begin() override;
		void Tick(float dt) override;

	private:
		static void OnCollision(CCollider* owner, CCollider* other);
		static void OnCollisionEnter(CCollider* owner, CCollider* other);
		static void OnCollisionExit(CCollider* owner, CCollider* other);
	};
}