#pragma once
#include "nata.h"
#include "EFollowCamera.h"
#include "EShip.h"
#include "EEnemy.h"
#include "EAsteroid.h"
#include "NDAsteroidPool.h"

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

		unsigned int AsteroidCount;

		static NObjectPool<EAsteroid>* AsteroidPool;
		static NObjectPool<EProjectile>* ProjectilePool;
		static NDAsteroidPool* DataPool;

	public:
		GSpaceShooter();

		void Awake() override;
		void Begin() override;
		void Tick(float dt) override;
	};
}