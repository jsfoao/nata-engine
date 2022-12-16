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
		vec3 Color;
		bool InputEnabled;

	public:
		EPlayer() : EEntity()
		{
			InputEnabled = true;
			MeshRenderer = AddComponent<CModelRenderer>();
			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			Model = new NModel("res\\models\\cube.obj");
			MeshRenderer->Init(shader, Model);
			
			Model->PropertyLayout.AddVec3("color");

			flipflop = true;
			MeshRenderer->SetVisibility(flipflop);
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
			Movement(dt);
			Model->PropertyLayout.SetVec3("color", Color);

			//Transform->Rotation.y += 0.1f;
			const float size = 2.f;
			Handles::DrawWireCube(Transform->Position, vec3(4.f), vec3(1.f, 0.f, 0.f));

			//std::vector<EPlayer*> entities = GetEntitiesOfType<EPlayer>(GetWorld());
		}

		void Movement(float dt)
		{
			if (!InputEnabled)
			{
				return;
			}
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
		}
	};
}