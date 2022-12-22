#include "EAsteroid.h"

namespace Nata
{
	EAsteroid::EAsteroid() : EEntity()
	{
		ModelRendererComp = AddComponent<CModelRenderer>();
		BoxColliderComp = AddComponent<CBoxCollider>();

		ModelRendererComp->PropertyLayout.AddVec3("color");

		BoxColliderComp->AddOnCollisionEnterCallback(OnCollisionEnter);
		
		Transform->Scale = vec3(0.05f);
		Color = vec3(1.f);
		BaseSpeed = 1.f;
		MoveSpeed = 10.f;
		Zlimit = 30.f;
	}

	void EAsteroid::OnEnable()
	{
		std::cout << "OnEnable" << std::endl;
		RotationAxis = Math::Random(vec3(-1.f), vec3(1.f));
		float scale = Math::Random(0.02f, 0.06f);
		Transform->Scale = vec3(scale);
		RotationSpeed = BaseSpeed / scale;
		BoxColliderComp->Bounds = Transform->Scale * 100.f;
	}

	void EAsteroid::Begin()
	{
		ModelRendererComp->PropertyLayout.SetVec3("color", Color);
	}

	void EAsteroid::Tick(float dt)
	{
		Transform->Rotation += RotationAxis * RotationSpeed * dt;
		//Transform->Position += vec3(0.f, 0.f, 1.f) * MoveSpeed * dt;

		if (Transform->Position.z >= Zlimit)
		{
			Destroy(GetWorld(), this);
		}
	}

	void EAsteroid::OnCollisionEnter(CCollider* owner, CCollider* other)
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