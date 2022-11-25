#pragma once
#include "ecs.h"
#include <iostream>

namespace Nata
{
	class OurGameMode : public NGameMode
	{
	public:
		void Begin()
		{
			std::cout << "Begin GameMode" << std::endl;
		}
	};
}