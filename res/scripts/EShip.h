#pragma once
#include "nata.h"
#include "core/comp/CModelRenderer.h"
#include "core/comp/CBoxCollider.h"
#include "scripts/EProjectile.h"

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

	public:
		EShip();
		void Begin() override;
		void Tick(float dt) override;
		void Shoot();

		void ProcessInput();

		static void OnCollisionEnter(CCollider* owner, CCollider* other);
		static void OnCollisionExit(CCollider* owner, CCollider* other);

		vec3 Lerp(vec3 start, vec3 end, float a)
		{
			return (start + a * (end - start));
		}

		vec3 MoveTowards(vec3 current, vec3 target, float maxDistanceDelta)
		{
			vec3 a = target - current;
			float magnitude = glm::length(a);
			if (magnitude <= maxDistanceDelta || magnitude == 0.f)
			{
				return target;
			}
			return current + a / magnitude * maxDistanceDelta;
		}

		float MoveTowards(float current, float target, float maxDelta)
		{
			if (glm::abs(target - current) <= maxDelta)
			{
				return target;
			}
			return current + glm::sign(target - current) * maxDelta;
		}
	};
}