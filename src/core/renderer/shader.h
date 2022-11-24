#pragma once
#include "GL/glew.h"
#include <iostream>
#include "core/core.h"
#include "utils/fileutils.h"
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

namespace Nata
{
	class Shader
	{
	public:
		unsigned int m_ID;

	private:
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		// Creates and loads
		Shader();
		Shader(const char* vertPath, const char* fragPath);

		/// <summary>
		/// Equivalent to glUseProgram(this)
		/// </summary>
		void Enable();

		/// <summary>
		/// Equivalent to glUseProgram(NULL)
		/// </summary>
		void Disable();
		inline unsigned int GetID() { return m_ID; }


		void SetUniform1i(const char* name, int value);
		void SetUniform1f(const char* name, float value);
		void SetUniform2f(const char* name, float v0, float v1);
		void SetUniform3f(const char* name, float v0, float v1, float v2);
		void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
		void SetUniform2f(const char* name, const vec2& v);
		void SetUniform3f(const char* name, const vec3& v);
		void SetUniform4f(const char* name, const vec4& v);
		void SetUniformMat4(const char* name, const mat4& matrix);
		
		/// <summary>
		/// Creates program and attaches shaders to it. Returns program id
		/// </summary>
		unsigned int Load();

	protected:
		unsigned int GetUniformLocation(const char* name);
	};
}