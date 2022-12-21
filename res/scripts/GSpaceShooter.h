#pragma once
#include "nata.h"
#include "EFollowCamera.h"
#include "EShip.h"
#include "EEnemy.h"
#include "EAsteroid.h"

namespace Nata
{
	class GSpaceShooter : public GGameMode
	{
	public:
		NShader* DiffuseShader;
		NShader* UnlitShader;

		NModel* AsteroidModel;
		NModel* ProjectileModel;

		EFollowCamera* Camera;
		EShip* Ship;
		float EnemySpawnZ;
		float SpawnTime;
		float CurrentTime;
		bool Spawning;
		float SpawnOffset;

	public:
		GSpaceShooter();

		void Begin() override;
		void Tick(float dt) override;
	};
}