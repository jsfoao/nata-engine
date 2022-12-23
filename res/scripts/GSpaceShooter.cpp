#include "GSpaceShooter.h"

namespace Nata
{
	GSpaceShooter::GSpaceShooter() : GGameMode()
	{
		Camera = nullptr;
		Ship = nullptr;
		EnemySpawnZ = -20.f;
	}

	void GSpaceShooter::Awake()
	{
		NModel::Init("res\\models\\LowPolyFiatUNO.obj");
		NModel::Init("res\\models\\rock_by_dommk.obj");
		NModel::Init("res\\models\\cube.obj");
		NShader::Init("src\\shaders\\diffuse.vert", "src\\shaders\\diffuse.frag");
		NShader::Init("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");

		Camera = Instantiate<EFollowCamera>(GetWorld());
		NEngine::Camera = Camera->CameraComp;

		Spawning = true;
		SpawnTime = 1.5f;
		EnemySpawnZ = -75.f;
		SpawnOffset = 4.f;

		Ship = Instantiate<EShip>(GetWorld());
		Camera->Target = Ship;
	}

	void GSpaceShooter::Begin()
	{
	}

	void GSpaceShooter::Tick(float dt)
	{
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
			vec2 dir = Math::Random(vec2(-1.f), vec2(1.f)) * SpawnOffset;
			EAsteroid* asteroid = Instantiate<EAsteroid>(GetWorld(), vec3(dir.x, dir.y, EnemySpawnZ));
			CurrentTime = 0.f;
		}
	}
}