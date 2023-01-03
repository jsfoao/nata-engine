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
			std::cout << "Entity: " << entity->Name << std::endl;
			std::cout << "ID: " << entity->GetID() << std::endl;
			std::cout << "Components:" << std::endl;
			for (auto& comp : entity->GetAllComponents())
			{
				std::cout << " > " << comp->Name << " ";
				if (comp->IsEnabled())
				{
					std::cout << "[X]";
				}
				else
				{
					std::cout << "[ ]";
				}
				std::cout << std::endl;
			}
		}
	}
}