#include "EProjectile.h"

namespace Nata
{
	NObjectPool<EProjectile>* EProjectile::ProjectilePool = nullptr;

	EProjectile::EProjectile() : EEntity()
	{
		MeshRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		NShader* shader = NAssetLoader::Get<NShader>("src\\shaders\\unlit.vert");
		Model = NAssetLoader::Get<NModel>("res\\models\\cube.obj");

		MeshRenderer->SetRenderableAndShader(Model, shader);
		MeshRenderer->PropertyLayout.AddVec3("color");

		BoxCollider->Bounds = vec3(1.f);
		BoxCollider->DrawHandles = true;

		Transform->Scale = vec3(0.3f);
		Direction = vec3(0.f, 0.f, 1.f);
		Speed = 100.f;
		LifeTime = 4.f;
	}

	void EProjectile::Begin()
	{
		MeshRenderer->PropertyLayout.SetVec3("color", vec3(1.f, 0.f, 0.f));
		CurrentTime = LifeTime;
	}

	void EProjectile::OnEnable()
	{
		CurrentTime = LifeTime;
	}

	void EProjectile::Tick(float dt)
	{
		Transform->Position += Direction * Speed * dt;
		CurrentTime -= dt;
		if (CurrentTime <= 0)
		{
			ProjectilePool->Delete(this);
			CurrentTime = LifeTime;
		}
	}
}