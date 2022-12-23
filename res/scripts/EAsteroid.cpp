#include "EAsteroid.h"

namespace Nata
{
	EAsteroid::EAsteroid() : EEntity()
	{
		ModelRendererComp = AddComponent<CModelRenderer>();
		BoxColliderComp = AddComponent<CBoxCollider>();

		Model = NAssetLoader::Get<NModel>("res\\models\\rock_by_dommk.obj");
		Shader = NAssetLoader::Get<NShader>("src\\shaders\\diffuse.vert");

		ModelRendererComp->SetRenderableAndShader(Model, Shader);
		ModelRendererComp->PropertyLayout.AddVec3("color");

		BoxColliderComp->AddOnCollisionEnterCallback(OnCollisionEnter);
		
		Transform->Scale = vec3(0.05f);
		Color = vec3(1.f);
		BaseSpeed = 1.f;
		MoveSpeed = 10.f;
		Zlimit = 30.f;
	}

	void EAsteroid::Begin()
	{
		RotationAxis = Math::Random(vec3(-1.f), vec3(1.f));
		float scale = Math::Random(0.02f, 0.06f);
		Transform->Scale = vec3(scale);
		RotationSpeed = BaseSpeed / scale;
		BoxColliderComp->Bounds = Transform->Scale * 100.f;
		ModelRendererComp->PropertyLayout.SetVec3("color", Color);
	}

	void EAsteroid::Tick(float dt)
	{
		Transform->Rotation += RotationAxis * RotationSpeed * dt;
		Transform->Position += vec3(0.f, 0.f, 1.f) * MoveSpeed * dt;

		if (Transform->Position.z >= Zlimit)
		{
			Destroy(GetWorld(), this);
		}
	}

	void EAsteroid::OnCollisionEnter(CCollider* owner, CCollider* other)
	{
		NWorld* world = owner->GetOwner()->GetWorld();
		EProjectile* proj = dynamic_cast<EProjectile*>(other->GetOwner());
		if (proj != nullptr)
		{
			Destroy(world, other->GetOwner());
			Destroy(world, owner->GetOwner());
		}
		EShip* ship = dynamic_cast<EShip*>(other->GetOwner());
		if (ship != nullptr)
		{
			Destroy(world, other->GetOwner());
			Destroy(world, owner->GetOwner());
		}
	}
}