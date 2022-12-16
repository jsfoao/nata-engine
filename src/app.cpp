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
			player1->Color = vec3(1.f, 0.f, 0.f);
			EPlayer* player2 = Instantiate<EPlayer>(world);
			player2->Color = vec3(0.f, 1.f, 0.f);
			player2->InputEnabled = false;
			player1->Target = player2;
			player2->Target = player1;
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}