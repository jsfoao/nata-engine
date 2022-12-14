#pragma once
#include "nata.h"
#include 

namespace Nata
{
	class CBoxCollider: public CComponent
	{
		void Begin() override
		{
			SuperBegin();
		}

		void Tick(float dt) override
		{
			SuperTick(dt);
			NWorld* world = GetOwner()->GetWorld();
			//std::vector<CBoxCollider> cols = GetComponentsOfType<CBoxCollider>(world);
		}
	};
}