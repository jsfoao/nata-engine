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
			NModel::Create("res\\models\\cube.obj", "res\\assets", "CubeTest");
			NModel::Create("res\\models\\sphere.obj", "res\\assets", "SphereTest");
			NShader::Create("res\\shaders\\diffuse.vert", "res\\shaders\\diffuse.frag", "res\\assets", "DiffuseShader");
			NShader::Create("res\\shaders\\unlit.vert", "res\\shaders\\unlit.frag", "res\\assets", "UnlitShader");
		}

		// runs before world tick
		static inline void Tick(float dt)
		{
		}
	};
}