#include "EShip.h"

namespace Nata
{
	NObjectPool<EProjectile>* EShip::ProjectilePool = nullptr;

	EShip::EShip() : EEntity()
	{
		MeshRenderer = AddComponent<CModelRenderer>();
		BoxCollider = AddComponent<CBoxCollider>();

		NShader* shader = NAssetLoader::Get<NShader>("res\\shaders\\diffuse.vert");
		Model = NAssetLoader::Get<NModel>("res\\models\\LowPolyFiatUNO.obj");

		MeshRenderer->SetRenderableAndShader(Model, shader);
		MeshRenderer->PropertyLayout.AddVec3("color");

		MeshRenderer->LocalRotation = vec3(0.f, 180.f, 0.f);
		MeshRenderer->LocalPosition = vec3(0.f, -1.f, 0.f);
		BoxCollider->Bounds = vec3(2.f, 2.f, 4.f);
		BoxCollider->DrawHandles = false;

		Input = vec3(0.f);
		Velocity = vec3(0.f);
		MaxSpeed = 1.f;
		Acceleration = 0.15f;
		Transform->Scale = vec3(1.f);
	}

	void EShip::Begin()
	{
		MeshRenderer->PropertyLayout.SetVec3("color", vec3(0.5f, 0.5f, 1.f));
	}

	void EShip::OnEnable()
	{
		Velocity = vec3(0.f);
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


		//Handles::DrawHandles(Transform, 5.f);
		//Handles::DrawLine(Transform->Position, Transform->Position - Transform->Forward * 50.f, vec3(1.f));
		Handles::DrawCircle(
			Transform->Position - Transform->Forward * 30.f,
			0.8f,
			NEngine::Camera->GetOwner()->Transform->Right,
			vec3(1.f));
		Handles::DrawSquare(Transform->Position - Transform->Forward * 15.f, vec2(1.5f), vec3(0.f, 0.f, 1.f), vec3(1.f));
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
		EProjectile* proj;
		proj = ProjectilePool->Create(posRight);
		proj->Direction = -Transform->Forward;
		proj = ProjectilePool->Create(posLeft);
		proj->Direction = -Transform->Forward;
	}
}