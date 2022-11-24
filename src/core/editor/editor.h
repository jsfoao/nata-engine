#pragma once
#include "core/glm_math.h"
#include "core/renderer/shader.h"
#include "core/renderer/mesh.h"
#include <vector>

using namespace std;
namespace Nata
{
	class Handles
	{
	public:
		Shader shader;
		mat4 view;
		mat4 projection;

		Handles();
        void DrawLine(const vec3& start, const vec3& end, const vec3& color);

		bool Init();
		void Update(mat4 view, mat4 projection);
	};
}