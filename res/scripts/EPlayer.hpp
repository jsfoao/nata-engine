#pragma once
#include "core/ecs/ecs.h"
#include "core/ecs/CMeshRenderer.hpp"
#include "core/editor/handles.h"
#include <iostream>

namespace Nata
{
	class EPlayer : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		bool flipflop;

	public:
		EPlayer() : EEntity()
		{
			MeshRenderer = AddComponent<CModelRenderer>();
			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			NModel* model = new NModel("res\\models\\cube.obj");
			MeshRenderer->Init(shader, model);

			MeshRenderer->GetShader()->Enable();
			MeshRenderer->GetShader()->SetUniform3f("color", vec3(1.f, 0.5f, 1.f));
			MeshRenderer->GetShader()->Disable();

			flipflop = true;
			MeshRenderer->SetVisibility(flipflop);
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
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

			//std::vector<EPlayer*> players = GetEntitiesOfType<EPlayer>(GetWorld());
			if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
			{
				flipflop = !flipflop;
				MeshRenderer->SetVisibility(flipflop);
			}

			//Transform->Rotation.y += 0.1f;
			const float size = 2.f;
			Handles::DrawHandles(Transform, vec3(2.f));
			Handles::DrawWireSphere(Transform->Position, 2.f, vec3(1.f, 0.f, 0.f));
		}
	};
}