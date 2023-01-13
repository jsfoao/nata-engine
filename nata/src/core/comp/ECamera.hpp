#pragma once
#include "ecs/ecs.h"
#include "comp/CCamera.h"
#include "nata_math.h"

namespace Nata
{
	class ECamera : public EEntity
	{
	public:
		CCamera* Camera;

	public:
		ECamera() : EEntity()
		{
			Camera = AddComponent<CCamera>();
			Transform->Rotation = vec3(-30.f, -90.f, 0.f);
			Transform->Position = vec3(0.f, 8.f, 10.f);
		}

		void Tick(float dt) override
		{
		}
	};
}