#include "EAsteroid.h"

namespace Nata
{
	NObjectPool<EAsteroid>* EAsteroid::AsteroidPool = nullptr;
	NObjectPool<EProjectile>* EAsteroid::ProjectilePool = nullptr;

	EAsteroid::EAsteroid() : EEntity()
	{
		ModelRendererComp = AddComponent<CModelRenderer>();
		BoxColliderComp = AddComponent<CBoxCollider>();

		Model = NAsset::Get<NModel>("res\\models\\rock_by_dommk.obj");
		Shader = NAsset::Get<NShader>("res\\shaders\\diffuse.vert");

		ModelRendererComp->SetRenderableAndShader(Model, Shader);
		ModelRendererComp->PropertyLayout.AddVec3("color");

		BoxColliderComp->AddOnCollisionEnterCallback(OnCollisionEnter);
		
		Transform->Scale = vec3(0.05f);
		RotationAxis = vec3(0.f);
		RotationSpeed = 0.f;
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
		BoxColliderComp->Transform->Scale = Transform->Scale * 100.f;
		ModelRendererComp->PropertyLayout.SetVec3("color", Color);
	}

	void EAsteroid::Tick(float dt)
	{
		Transform->Rotation += RotationAxis * RotationSpeed * dt;
		Transform->Position += vec3(0.f, 0.f, 1.f) * MoveSpeed * dt;

		if (Transform->Position.z >= Zlimit)
		{
			AsteroidPool->Delete(this);
		}
	}

	void EAsteroid::OnCollisionEnter(CCollider* owner, CCollider* other)
	{
		NWorld* world = owner->GetOwner()->GetWorld();
		EProjectile* proj = dynamic_cast<EProjectile*>(other->GetOwner());
		if (proj != nullptr)
		{
			EAsteroid::AsteroidPool->Delete(owner->GetOwner());
			EAsteroid::ProjectilePool->Delete(other->GetOwner());
		}

		//EShip* ship = dynamic_cast<EShip*>(other->GetOwner());
		//if (ship != nullptr)
		//{
		//	EAsteroid::Pool->Delete(owner->GetOwner());
		//	Destroy(world, other->GetOwner());
		//}
	}
}