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
		DiffuseShader = new NShader("src\\shaders\\diffuse.vert", "src\\shaders\\diffuse.frag");
		AsteroidModel = new NModel("res\\models\\rock_by_dommk.obj");

		Camera = Instantiate<EFollowCamera>(GetWorld());
		NEngine::Camera = Camera->CameraComp;

		Spawning = true;
		SpawnTime = 1.5f;
		EnemySpawnZ = -75.f;
		SpawnOffset = 4.f;

		EAsteroid* asteroid1 = Instantiate<EAsteroid>(GetWorld(), vec3(3.f, 0.f, 0.f));
		EAsteroid* asteroid2 = Instantiate<EAsteroid>(GetWorld(), vec3(-3.f, 0.f, 0.f));
		asteroid1->ModelRendererComp->SetRenderableAndShader(AsteroidModel, DiffuseShader);
		asteroid2->ModelRendererComp->SetRenderableAndShader(AsteroidModel, DiffuseShader);
		asteroid1->Color = vec3(1.f, 0.f, 0.f);
		asteroid2->Color = vec3(0.f, 1.f, 0.f);
	}

	void GSpaceShooter::Begin()
	{
	}

	void GSpaceShooter::Tick(float dt)
	{
		//for (int i = -2; i < 10; i++)
		//{
		//	Handles::DrawSquare(vec3(0.f, 0.f, i * -15.f), vec2(16.f, 9.f), vec3(0.f, 0.f, 1.f), vec3(0.4f));
		//}

		//if (!Spawning)
		//{
		//	return;
		//}
		//CurrentTime += dt;
		//if (CurrentTime >= SpawnTime)
		//{
		//	vec2 dir = Math::Random(vec2(-1.f), vec2(1.f)) * SpawnOffset;
		//	EAsteroid* asteroid = Instantiate<EAsteroid>(GetWorld(), vec3(dir.x, dir.y, EnemySpawnZ));
		//	asteroid->ModelRendererComp->Init(DiffuseShader, AsteroidModel);
		//	CurrentTime = 0.f;
		//}
	}
}