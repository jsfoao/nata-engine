#pragma once
#include "nata.h"
#include "core/comp/CModelRenderer.h"
#include "core/comp/CBoxCollider.h"

namespace Nata
{
	class EProjectile : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		CBoxCollider* BoxCollider;
		NModel* Model;
		vec3 Direction;
		float Speed;
		float LifeTime;
		float CurrentTime;

		static NObjectPool<EProjectile>* ProjectilePool;

	public:
		EProjectile();
		void Begin() override;
		void OnEnable() override;
		void Tick(float dt) override;

		static void OnCollisionEnter(CCollider* owner, CCollider* other);
		static void OnCollisionExit(CCollider* owner, CCollider* other);
	};
}