#include "EEnemy.h"

namespace Nata
{
	EEnemy::EEnemy() : EEntity()
	{
		ModelRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		BoxCollider->AddOnCollisionEnterCallback(OnCollisionEnter);

		ModelRenderer->SetRenderableAndShader(Model, Shader);
		BoxCollider->Bounds = vec3(2.f);

		Speed = 10.f;
		Zlimit = 10.f;
	}

	void EEnemy::Begin()
	{
	}

	void EEnemy::Tick(float dt)
	{
		Transform->Position += vec3(0.f, 0.f, 1.f) * Speed * dt;

		if (Transform->Position.z >= Zlimit)
		{
			Destroy(GetWorld(), this);
		}
	}

	void EEnemy::OnCollisionEnter(CCollider* owner, CCollider* other)
	{
		EProjectile* proj = dynamic_cast<EProjectile*>(other->GetOwner());
		if (proj != nullptr)
		{
			std::cout << "Killed by projectile" << std::endl;
			Destroy(other->GetOwner()->GetWorld(), other->GetOwner());
			Destroy(owner->GetOwner()->GetWorld(), owner->GetOwner());
		}
	}
}
