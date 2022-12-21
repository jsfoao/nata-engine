#pragma once
#include "nata.h"
#include "core/comp/CModelRenderer.h"
#include "core/comp/CBoxCollider.h"

namespace Nata
{
	class EPlayer : public EEntity
	{
	public:
		CModelRenderer* MeshRenderer;
		CBoxCollider* BoxCollider;
		NModel* Model;
		bool flipflop;
		vec3 Color;
		bool InputEnabled;

	public:
		EPlayer() : EEntity()
		{
			MeshRenderer = AddComponent<CModelRenderer>();
			BoxCollider = AddComponent<CBoxCollider>();

			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			Model = new NModel("res\\models\\cube.obj");
			MeshRenderer->Init(shader, Model);

			Color = vec3(0.f);
			InputEnabled = true;
			flipflop = true;

			MeshRenderer->SetVisibility(flipflop);
			Model->PropertyLayout.AddVec3("color");

			BoxCollider->Bounds = vec3(3.f);
		}

		void Begin() override
		{
		}

		void Tick(float dt) override
		{
			Handles::DrawHandles(Transform, 2.f);

			Movement(dt);
			Model->PropertyLayout.SetVec3("color", Color);
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

		vec3 Lerp(vec3 start, vec3 end, float a)
		{
			return (start + a * (end - start));
		}
	};
}