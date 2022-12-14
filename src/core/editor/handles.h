#pragma once
#include "nata.h"

namespace Nata
{
	class Handles
	{
	public:
		static NShader* Shader;

	public:
		static bool Init();

		static void DrawLine(const vec3& start, const vec3& end, const vec3& color);
		static void DrawWireCube(const vec3& pos, const vec3& size, const vec3& color);
		static void DrawHandles(const CTransform* transform, const vec3& size);
		static void DrawWireSphere(const vec3& pos, const float radius, const vec3& color);
		static void DrawCircle(const vec3& pos, const float radius, const vec3& normal, const vec3& color, const int segments = 16);
	};
}