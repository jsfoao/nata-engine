#pragma once
#include "ecs.h"
#include <iostream>

namespace Nata
{
	class NOurGameMode : public NGameMode
	{
	public:
		NOurGameMode(){}

		void Begin()
		{
			std::cout << "Begin GameMode" << std::endl;
		}
	};
}