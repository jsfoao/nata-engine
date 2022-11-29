#pragma once
#include "shader.h"
#include "core/glm_math.h"

namespace Nata
{
	class NRenderable
	{
	public:
		NShader* Shader;
		vec3 Position;
		vec3 Rotation;
		vec3 Scale;

	public:
		NRenderable()
		{
			Position = vec3(0.f);
			Rotation = vec3(0.f);
			Scale = vec3(1.f);
		}

		virtual void Draw(){};
	};
}