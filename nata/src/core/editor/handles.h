#pragma once
#include "nata.h"
#include "core/renderer/mesh.h"
#include "core/renderer/buffer.h"

namespace Nata
{
	class Handles
	{
	public:
		static NShader* Shader;
		static bool m_Enabled;

	protected:
		static NMesh* m_LineMesh;
		static std::vector<float> m_LineVertices;

	public:
		static bool Init();
		static void SetEnable(bool enabled);

		static void DrawLine(const vec3& start, const vec3& end, const vec3& color);
		static void DrawWireCube(const vec3& pos, const vec3& size, const vec3& color);
		static void DrawWireCube(const vec3& pos, const vec3& rot, const vec3& size, const vec3& color);
		static void DrawHandles(const CTransform* transform, const float size);
		static void DrawWireSphere(const vec3& pos, const float radius, const vec3& color);
		static void DrawCircle(const vec3& pos, const float radius, const vec3& normal, const vec3& color, const int segments = 16);
		static void DrawSquare(const vec3& pos, const vec2& size, const vec3& normal, const vec3& color);
	};
}