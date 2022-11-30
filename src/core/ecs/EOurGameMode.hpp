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
			Instantiate<EOurObject>(GetWorld());
		}

		void Tick(float dt) override 
		{
			if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
			{
				Destroy(GetWorld(), object1);
			}

			std::cout << GetWorld()->GetAllEntities().size() << std::endl;
		}
	};
}