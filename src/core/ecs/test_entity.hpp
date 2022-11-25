#pragma once
#include "ecs.h"
#include "transform_comp.hpp"
#include <iostream>

namespace Nata
{
	class OurObject : public NEntity
	{
	public:
		Transform* transform;

		OurObject()
		{
			transform = AddComponent<Transform>();
		}

		void Begin()
		{
			std::cout << "Begin Entity" << std::endl;
		}
	};
}