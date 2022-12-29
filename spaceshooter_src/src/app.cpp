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
			NEngine::World = NWorld::Init();
			NEngine::World->SetGameMode(GGameMode::Init<GSpaceShooter>());
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}