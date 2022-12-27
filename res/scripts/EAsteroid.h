#pragma once
#include "nata.h"
#include "core/comp/CModelRenderer.h"
#include "core/comp/CBoxCollider.h"
#include "EProjectile.h"
#include "EShip.h"

namespace Nata
{
	class EAsteroid : public EEntity
	{
	public:
		CModelRenderer* ModelRendererComp;
		CBoxCollider* BoxColliderComp;
		NModel* Model;
		NShader* Shader;

		vec3 Color;

		// rotation
		float BaseSpeed;
		float RotationSpeed;
		vec3 RotationAxis;

		// movement
		float MoveSpeed;
		float Zlimit;

	public:
		EAsteroid();
		void Begin() override;
		void Tick(float dt) override;

		static void OnCollisionEnter(CCollider* owner, CCollider* other);
	};
}