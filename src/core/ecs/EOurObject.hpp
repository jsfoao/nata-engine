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
			MeshRenderer->Shader = shader;
			MeshRenderer->Model = model;
			MeshRenderer->Model->Shader = shader;

			Offset = false;
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
			if (Offset == true)
			{
				Transform->Position.y = sin(NTime::Time) * 3.f;
				Transform->Position.x = -2.f;
				MeshRenderer->Shader->Enable();
				MeshRenderer->Shader->SetUniform3f("color", vec3(1.f, 0.5f, 1.f));
				MeshRenderer->Shader->Disable();
			}
			else
			{
				Transform->Position.y = sin(NTime::Time) * 2.f;
				MeshRenderer->Shader->Enable();
				MeshRenderer->Shader->SetUniform3f("color", vec3(1.f, sin(NTime::Time), 1.f));
				MeshRenderer->Shader->Disable();
			}
		}
	};
}