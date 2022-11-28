#pragma once
#include "ecs.h"
#include "CMeshRenderer.hpp"
#include <iostream>

namespace Nata
{
	class EOurObject : public EEntity
	{
	public:
		CMeshRenderer* MeshRenderer;

	public:
		EOurObject() : EEntity()
		{
			MeshRenderer = AddComponent<CMeshRenderer>();
		}

		void Begin() override
		{
			std::cout << "Begin from base" << std::endl;
		}

		void Tick(float deltaTime) override
		{

		}
	};
}