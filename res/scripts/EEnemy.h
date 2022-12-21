#pragma once
#include "nata.h"
#include "core/comp/CModelRenderer.h"
#include <core/comp/CBoxCollider.h>
#include "EProjectile.h"


namespace Nata
{
	class EEnemy : public EEntity
	{
	public:
		CModelRenderer* ModelRenderer;
		CBoxCollider* BoxCollider;
		NModel* Model;
		NShader* Shader;
		float Speed;
		float Zlimit;

	public:
		EEnemy();
		void Begin() override;
		void Tick(float dt) override;

		static void OnCollisionEnter(CCollider* owner, CCollider* other);
	};
}