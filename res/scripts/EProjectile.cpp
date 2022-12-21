#include "EProjectile.h"

namespace Nata
{
	EProjectile::EProjectile() : EEntity()
	{
		MeshRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
		Model = new NModel("res\\models\\cube.obj");
		MeshRenderer->Init(shader, Model);

		Model->PropertyLayout.AddVec3("color");
		Model->PropertyLayout.SetVec3("color", vec3(1.f, 1.f, 0.f));

		BoxCollider->Bounds = vec3(1.f);
		BoxCollider->DrawHandles = true;

		Transform->Scale = vec3(0.3f);
		Direction = vec3(0.f, 0.f, 1.f);
		Speed = 100.f;
		LifeTime = 4.f;
	}

	void EProjectile::Begin()
	{
	}

	void EProjectile::Tick(float dt)
	{
		Transform->Position += Direction * Speed * dt;
		LifeTime -= dt;
		if (LifeTime <= 0)
		{
			Destroy(GetWorld(), this);
			std::cout << "Destroyed Projectile" << std::endl;
		}
	}
}