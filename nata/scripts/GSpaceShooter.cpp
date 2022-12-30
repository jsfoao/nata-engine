#include "GSpaceShooter.h"

namespace Nata
{
	NObjectPool<EAsteroid>* GSpaceShooter::AsteroidPool = nullptr;
	NObjectPool<EProjectile>* GSpaceShooter::ProjectilePool = nullptr;
	NDAsteroidPool* GSpaceShooter::DataPool = nullptr;

	GSpaceShooter::GSpaceShooter() : GGameMode()
	{
		Camera = nullptr;
		Ship = nullptr;
		EnemySpawnZ = -20.f;
	}

	void GSpaceShooter::Awake()
	{
		NModel::Create("res\\models\\LowPolyFiatUNO.obj", "assets\\models", "car");
		NModel::Create("res\\models\\rock_by_dommk.obj", "assets\\models", "rock");
		NShader::Create("res\\shaders\\diffuse.vert", "res\\shaders\\diffuse.frag", "assets\\shaders", "diffuse");

		DataPool = new NDAsteroidPool(1000);
		ProjectilePool = new NObjectPool<EProjectile>(500);

		// Initiliazing pools on objects, clean this up
		EAsteroid::ProjectilePool = ProjectilePool;
		EShip::ProjectilePool = ProjectilePool;
		EProjectile::ProjectilePool = ProjectilePool;

		Camera = Instantiate<EFollowCamera>(GetWorld());
		NEngine::Camera = Camera->CameraComp;

		Spawning = true;
		SpawnTime = 0.2f;
		EnemySpawnZ = -75.f;
		SpawnOffset = 10.f;

		AsteroidCount = 0;

		Ship = Instantiate<EShip>(GetWorld());
		Camera->Target = Ship;
	}

	void GSpaceShooter::Begin()
	{
		DataPool->world = GetWorld();
		DataPool->Begin();
	}

	void GSpaceShooter::Tick(float dt)
	{
		if (NEngine::Input->GetKeyDown(GLFW_KEY_R))
		{
			DataPool->Clear();
			Ship->Transform->Position = vec3(0.f);
		}

		DataPool->Tick(dt);

		for (int i = -2; i < 10; i++)
		{
			Handles::DrawSquare(vec3(0.f, 0.f, i * -15.f), vec2(16.f, 9.f), vec3(0.f, 0.f, 1.f), vec3(0.4f));
		}

		if (!Spawning)
		{
			return;
		}
		CurrentTime += dt;
		if (CurrentTime >= SpawnTime)
		{
			int id = DataPool->EnableID();
			vec2 dir = Math::Random(vec2(-1.f), vec2(1.f)) * SpawnOffset;
			DataPool->Transform[id].Position = vec3(dir.x, dir.y, -100.f);
	
			CurrentTime = 0.f;
		}
	}
}