#pragma once
#include "nata.h"

namespace Nata
{
	class NWindow;
	class CModelRenderer : public CComponent
	{
	public:
		NShader* Shader;
		NTexture* Texture;
		NModel* Model;

	public:
		void Tick(float dt) override
		{
			Model->Position = m_Owner->Transform->Position;
			Model->Rotation = m_Owner->Transform->Rotation;
			NWindow* window = NEngine::Window;
			window->GetRenderer()->Submit(Model);
		}
	};
}