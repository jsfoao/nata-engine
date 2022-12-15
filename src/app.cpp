#pragma once 
#include "nata.h"
#include "EPlayer.hpp"
#include "core/ecs/ECamera.hpp"
#include "NShooterGameMode.hpp"

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
			NShooterGameMode* gameMode = new NShooterGameMode();
			world->SetGameMode(gameMode);

			ECamera* camera = Instantiate<ECamera>(world);
			NEngine::Camera = camera->Camera;

			camera->Transform->Position = vec3(0.f, 0.f, 20.f);

			EPlayer* player1 = Instantiate<EPlayer>(world);
			//EPlayer* player2 = Instantiate<EPlayer>(world);
			//player2->InputEnabled = false;
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}