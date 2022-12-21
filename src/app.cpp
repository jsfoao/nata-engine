#pragma once 
#include "nata.h"
#include "EShip.h"
#include "core/ecs/ECamera.hpp"
#include "scripts/GSpaceShooter.h"

namespace Nata
{
	class App
	{
	public:
		// first initialization of world and objects
		static inline void Begin()
		{
			NWorld* world = new NWorld();
			NEngine::World = world;
			GSpaceShooter* gameMode = new GSpaceShooter();
			world->SetGameMode(gameMode);
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}