#include "EShip.h"

namespace Nata
{
	EShip::EShip() : EEntity()
	{
		MeshRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		NShader* shader = new NShader("src\\shaders\\diffuse.vert", "src\\shaders\\diffuse.frag");
		Model = new NModel("res\\models\\LowPolyFiatUNO.obj");
		MeshRenderer->Init(shader, Model);

		Model->PropertyLayout.AddVec3("color");
		Model->PropertyLayout.SetVec3("color", vec3(1.f, 1.f, 1.f));
		MeshRenderer->Rotation = vec3(0.f, 180.f, 0.f);
		MeshRenderer->Position = vec3(0.f, -1.f, 0.f);
		BoxCollider->Bounds = vec3(2.f, 2.f, 4.f);
		BoxCollider->DrawHandles = true;

		Input = vec3(0.f);
		Velocity = vec3(0.f);
		MaxSpeed = 2.f;
		Acceleration = 0.25f;
		Transform->Scale = vec3(1.f);
	}

	void EShip::Begin()
	{
	}

	void EShip::Tick(float dt)
	{
		ProcessInput();
		if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
		{
			Shoot();
		}

		Velocity.x = MoveTowards(Velocity.x, Input.x * MaxSpeed, Acceleration * dt);
		Velocity.y = MoveTowards(Velocity.y, Input.y * MaxSpeed, Acceleration * dt);
		Transform->Rotation.z = Velocity.x * 120.f;
		Transform->Rotation.x = Velocity.y * 120.f;
		Transform->Rotation.y = -Velocity.x * 120.f;
		Transform->Position += Velocity;

		Handles::DrawHandles(Transform, 5.f);
		Handles::DrawLine(Transform->Position, Transform->Position + Transform->Forward * 100.f, vec3(0.f, 0.f, 1.f));
	}

	void EShip::ProcessInput()
	{
		Input.x = NEngine::Input->GetKeyHold(GLFW_KEY_D) - NEngine::Input->GetKeyHold(GLFW_KEY_A);
		Input.y = NEngine::Input->GetKeyHold(GLFW_KEY_W) - NEngine::Input->GetKeyHold(GLFW_KEY_S);
		if (glm::length(Input) > 1)
		{
			Input = glm::normalize(Input);
		}
	}

	void EShip::Shoot()
	{
		Instantiate<EProjectile>(GetWorld(), Transform->Position + Transform->Forward * 1.f);
		//projectile->Direction = Transform->Forward;
	}
}