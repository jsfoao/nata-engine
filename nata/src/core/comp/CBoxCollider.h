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
	protected:
		NBox m_Box;

	public:
		CBoxCollider();
		inline NBox GetBox() { return m_Box; }
		void Begin() override;
		void Tick(float dt) override;
		void OnDisable() override;

	private:
		static void OnCollision(CCollider* owner, CCollider* other);
		static void OnCollisionEnter(CCollider* owner, CCollider* other);
		static void OnCollisionExit(CCollider* owner, CCollider* other);
	};
}