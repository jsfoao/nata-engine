#pragma once
#include "nata.h"

namespace Nata
{
	class CMeshRenderer : public CComponent
	{
	public:
		NShader* Shader;
		NTexture* Texture;
		NModel* Model;

	public:
		void Tick(float deltaTime) override
		{
			Model->Position = m_Owner->Transform->Position;
			Window->GetRenderer()->Submit(Model);
		}
	};
}