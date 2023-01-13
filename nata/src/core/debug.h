#pragma once
#include <iostream>
#include <vector>
#include "ecs/ecs.h"
namespace Nata
{
	namespace Debug
	{
		static void Log(EEntity* entity)
		{
			if (entity->IsEnabled())
			{
				std::cout << "[X]";
			}
			else
			{
				std::cout << "[ ]";
			}
			std::cout << " ENTITY" << std::endl;
			std::cout << "> Name: " << entity->Name << std::endl;
			std::cout << "> ID: " << entity->GetID() << std::endl;
			std::cout << "> Components:" << std::endl;
			for (auto& comp : entity->GetAllComponents())
			{
				std::cout << " ";
				if (comp->IsPreEnabled() && !comp->IsEnabled())
				{
					std::cout << "[x]";
				}
				else if (comp->IsEnabled())
				{
					std::cout << "[X]";
				}
				else
				{
					std::cout << "[ ]";
				}
				std::cout << " " << comp->Name << std::endl;
			}
		}
	}
}