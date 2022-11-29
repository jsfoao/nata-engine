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

	public:
		EOurObject() : EEntity()
		{
			MeshRenderer = AddComponent<CModelRenderer>();
			NShader* shader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
			NModel* model = new NModel("res\\models\\teapot.obj");
			MeshRenderer->Shader = shader;
			MeshRenderer->Model = model;
			MeshRenderer->Model->Shader = shader;
		}

		void Begin() override
		{
			std::cout << "Begin from base" << std::endl;
		}

		void Tick(float dt) override
		{
			Transform->Position.y = sin(NTime::Time) * 2.f;
		}
	};
}