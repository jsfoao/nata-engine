#pragma once
#include <string>
#include <vector>
#include "nata_math.h"
#include "core/renderer/shader.h"

namespace Nata
{
	template <class T>
	class NPropertyBlock
	{
	public:
		const char* Name;
		T Value;

	public:
		NPropertyBlock()
		{
			Name = nullptr;
		}
		NPropertyBlock(const char* name)
		{
			Name = name;
		}
		NPropertyBlock(const char* name, T value)
		{
			Name = name;
			Value = value;
		}
	};

	class NPropertyBlockLayout
	{
	protected:
		std::vector<NPropertyBlock<vec3>> m_Vec3;
		std::vector<NPropertyBlock<float>> m_Float;
		std::vector<NPropertyBlock<mat4>> m_Matrix;
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

		void AddVec3(const char* name)
		{
			NPropertyBlock<vec3> prop(name);
			m_Vec3.push_back(prop);
		}

		void AddFloat(const char* name)
		{
			NPropertyBlock<float> prop(name);
			m_Float.push_back(prop);
		}

		void AddMatrix(const char* name)
		{
			NPropertyBlock<mat4> prop(name);
			m_Matrix.push_back(prop);
		}

		void SetVec3(const char* name, vec3 value)
		{
			for (int i = 0; i < m_Vec3.size(); i++)
			{
				if (m_Vec3[i].Name == name)
				{
					m_Vec3[i].Value = value;
				}
			}
		}

		void SetFloat(const char* name, float value)
		{
			for (int i = 0; i < m_Float.size(); i++)
			{
				if (m_Float[i].Name == name)
				{
					m_Float[i].Value = value;
				}
			}
		}

		void SetMatrix(const char* name, mat4 value)
		{
			for (int i = 0; i < m_Matrix.size(); i++)
			{
				if (m_Matrix[i].Name == name)
				{
					m_Matrix[i].Value = value;
				}
			}
		}

		void SetProperties()
		{
			m_Shader->Enable();
			for (int i = 0; i < m_Vec3.size(); i++)
			{
				m_Shader->SetUniform3f(m_Vec3[i].Name, m_Vec3[i].Value);
			}
			for (int i = 0; i < m_Float.size(); i++)
			{
				m_Shader->SetUniform1f(m_Float[i].Name, m_Float[i].Value);
			}
			for (int i = 0; i < m_Matrix.size(); i++)
			{
				m_Shader->SetUniformMat4(m_Matrix[i].Name, m_Matrix[i].Value);
			}
		}
	};
}