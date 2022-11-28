#pragma once
#include "shader.h"
#include "core/glm_math.h"

namespace Nata
{
	class NRenderable
	{
	public:
		NShader Shader;
		vec3 Position;

	public:
		NRenderable()
		{
			Position = vec3(0.f);
		}

		virtual void Draw(){};
	};
}