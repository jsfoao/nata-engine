#pragma once
#include "ecs.h"
#include "core/comp/CCamera.h"
#include "core/glm_math.h"

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
			Transform->Rotation = vec3(0.f, -90.f, 0.f);
			Transform->Position = vec3(0.f, 0.f, 10.f);
		}

		void Tick(float dt) override
		{
		}
	};
}