#pragma once
#include "ecs.h"
#include "CMeshRenderer.hpp"
#include <iostream>

namespace Nata
{
	class EOurObject : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		bool Offset;

	public:
		EOurObject() : EEntity()
		{
			MeshRenderer = AddComponent<CModelRenderer>();
			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			NModel* model = new NModel("res\\models\\teapot.obj");
			MeshRenderer->SetAll(shader, model);
			
			MeshRenderer->GetShader()->Enable();
			MeshRenderer->GetShader()->SetUniform3f("color", vec3(1.f, 0.5f, 1.f));
			MeshRenderer->GetShader()->Disable();
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
			if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
			{
				std::cout << "Down" << std::endl;
			}
			if (NEngine::Input->GetKeyUp(GLFW_KEY_SPACE))
			{
				std::cout << "Up" << std::endl;
			}
		}
	};
}