#pragma once
#include "nata.h"
#include "comp/CModelRenderer.h"
#include "comp/CBoxCollider.h"
#include "EProjectile.h"

namespace Nata
{
	class EShip : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		CBoxCollider* BoxCollider;
		NModel* Model;
		vec3 Input;
		vec3 Velocity;
		float MaxSpeed;
		float Acceleration;
		float RotationOffset;

		static NObjectPool<EProjectile>* ProjectilePool;

	public:
		EShip();
		void Begin() override;
		void OnEnable() override;
		void Tick(float dt) override;
		void Shoot();

		void ProcessInput();

		static void OnCollisionEnter(CCollider* owner, CCollider* other);
		static void OnCollisionExit(CCollider* owner, CCollider* other);
	};
}