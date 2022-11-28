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
	};
}