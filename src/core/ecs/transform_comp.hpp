#pragma once
#include "ecs.h"
#include <iostream>

namespace Nata
{
	class Transform : public NComponent
	{
	public:
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;

		Transform()
		{
			Position = vec3(0.f, 0.f, 0.f);
			Scale = vec3(1.f, 1.f, 1.f);
			Rotation = vec3(0.f, 0.f, 0.f);
		}

		void Begin()
		{
			std::cout << "Begin Transform Component" << std::endl;
		}
	};
}