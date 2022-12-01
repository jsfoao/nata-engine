#pragma once
#include "core/core.h"
#include "ecs.h"
#include <iostream>
#include "EOurObject.hpp"

namespace Nata
{
	class EOurObject;

	class NOurGameMode : public NGameMode
	{
	public:
		EOurObject* object1;
		EOurObject* object2;

	public:
		NOurGameMode(){}

		void Begin() override
		{
		}

		void Tick(float dt) override 
		{
		}
	};
}