#include "EShip.h"

namespace Nata
{
	EShip::EShip() : EEntity()
	{
		MeshRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		NShader* shader = new NShader("src\\shaders\\diffuse.vert", "src\\shaders\\diffuse.frag");
		Model = new NModel("res\\models\\LowPolyFiatUNO.obj");
		MeshRenderer->SetRenderableAndShader(Model, shader);

		MeshRenderer->LocalRotation = vec3(0.f, 180.f, 0.f);
		MeshRenderer->LocalPosition = vec3(0.f, -1.f, 0.f);
		BoxCollider->Bounds = vec3(2.f, 2.f, 4.f);
		BoxCollider->DrawHandles = true;

		Input = vec3(0.f);
		Velocity = vec3(0.f);
		MaxSpeed = 1.f;
		Acceleration = 0.15f;
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

		Velocity.x = Math::MoveTowards(Velocity.x, Input.x * MaxSpeed, Acceleration * dt);
		Velocity.y = Math::MoveTowards(Velocity.y, Input.y * MaxSpeed, Acceleration * dt);
		Transform->Rotation.z = Velocity.x * 120.f;
		Transform->Rotation.x = Velocity.y * 120.f;
		Transform->Rotation.y = -Velocity.x * 120.f;
		Transform->Position += Velocity;


		Handles::DrawHandles(Transform, 5.f);
		Handles::DrawLine(Transform->Position, Transform->Position - Transform->Forward * 100.f, vec3(1.f));
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
		vec3 posRight = Transform->Position - Transform->Forward * 1.f + Transform->Right * 1.f;
		vec3 posLeft = Transform->Position - Transform->Forward * 1.f - Transform->Right * 1.f;
		Instantiate<EProjectile>(GetWorld(), posRight)->Direction = -Transform->Forward;
		Instantiate<EProjectile>(GetWorld(), posLeft)->Direction = -Transform->Forward;
	}
}