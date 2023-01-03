#pragma once
#include "GL/glew.h"
#include <iostream>
#include "utils/fileutils.h"
#include <vector>
#include "core/asset_loader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

namespace Nata
{
	class NShader : public NAsset
	{
	public:
		unsigned int m_ID;

	private:
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		// Creates and loads
		NShader();
		NShader(const char* vertPath, const char* fragPath);

		// equivalent to glUseProgram(this)
		void Enable();

		// equivalent to glUseProgram(NULL)
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
		
		// Creates program and attaches shaders to it
		bool Load() override;

		static bool Create(std::string vertPath, std::string fragPath, std::string dest, std::string name);

	protected:
		unsigned int GetUniformLocation(const char* name);
	};
}