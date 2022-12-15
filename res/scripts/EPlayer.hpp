#pragma once
#include "nata.h"
#include "core/ecs/CMeshRenderer.hpp"

namespace Nata
{
	class EPlayer : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		NModel* Model;
		bool flipflop;
		vec3* Color;

	public:
		EPlayer() : EEntity()
		{
			MeshRenderer = AddComponent<CModelRenderer>();
			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			Model = new NModel("res\\models\\cube.obj");
			MeshRenderer->Init(shader, Model);
			Color = new vec3(0.f, 1.f, 0.f);
			Model->PropertyLayout.Bind(shader);
			//Model->PropertyLayout.AddVec3(NVec3Property("color", Color));
			//Model->SetPropertyCallback(ModelPropertyCallback);

			flipflop = true;
			MeshRenderer->SetVisibility(flipflop);
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
			Color = new vec3(1.f, 0.f, 0.f);

			vec2 input = vec2(0.f);
			float speed = 1.f;
			if (NEngine::Input->GetKeyHold(GLFW_KEY_LEFT))
			{
				input.x = -1;
			}
			if (NEngine::Input->GetKeyHold(GLFW_KEY_RIGHT))
			{
				input.x = 1;
			}
			if (NEngine::Input->GetKeyHold(GLFW_KEY_UP))
			{
				input.y = 1;
			}
			if (NEngine::Input->GetKeyHold(GLFW_KEY_DOWN))
			{
				input.y = -1;
			}
			Transform->Position.x += input.x * speed * dt;
			Transform->Position.y += input.y * speed * dt;

			if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
			{
				flipflop = !flipflop;
				MeshRenderer->SetVisibility(flipflop);
			}

			//Transform->Rotation.y += 0.1f;
			const float size = 2.f;

			Handles::DrawWireCube(Transform->Position, vec3(4.f), vec3(1.f, 0.f, 0.f));
		}

		//static void ModelPropertyCallback(NShader* shader)
		//{
		//	shader->SetUniform3f("color", vec3(1.f, 0.5f, 1.f));
		//}
	};
}