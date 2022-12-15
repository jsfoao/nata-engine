#pragma once
#include <string>
#include <vector>
#include "core/glm_math.h"
#include "core/renderer/shader.h"

namespace Nata
{
	class NVec3Property
	{
	public:
		const char* Name;
		vec3 Value;

	public:
		NVec3Property()
		{
			Name = nullptr;
			Value = nullptr;
		}
		NVec3Property(const char* name, vec3 value)
		{
			Name = name;
			Value = value;
		}
	};

	class NPropertyBlockLayout
	{
	protected:
		std::vector<NVec3Property> m_Vec3Props;
		NShader* m_Shader;

	public:
		NPropertyBlockLayout()
		{
			m_Shader = nullptr;
		}

		void Bind(NShader* shader)
		{
			m_Shader = shader;
		}

		void AddVec3(NVec3Property prop)
		{
			m_Vec3Props.push_back(prop);
		}

		void SetProperties()
		{
			for (NVec3Property prop : m_Vec3Props)
			{
				m_Shader->SetUniform3f(prop.Name, prop.Value);
			}
		}
	};
}