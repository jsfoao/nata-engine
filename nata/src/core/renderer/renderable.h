#pragma once
#include "nata_math.h"
#include "core/renderer/propertyblock.h"

namespace Nata
{
	class NShader;
	class NRenderable
	{
	public:
		NShader* Shader;
		vec3 Position;
		vec3 Rotation;
		vec3 Scale;

	public:
		NRenderable();
		virtual void Draw() {};
	};
}