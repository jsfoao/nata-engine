#pragma once 
#include "nata.h"
#include "EShip.h"
#include "comp/ECamera.hpp"
#include "GSpaceShooter.h"
#include "GTests.h"

namespace Nata
{
	class App
	{
	public:
		// first initialization of world and objects
		static inline void Begin()
		{
			NEngine::World = NWorld::Init();
			NEngine::World->SetGameMode(GGameMode::Init<GTests>());
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}