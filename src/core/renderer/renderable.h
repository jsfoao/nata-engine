#pragma once
#include "core/glm_math.h"
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
		NPropertyBlockLayout PropertyLayout;

	protected:
		void(*propCb)(NShader*);
		bool m_PropertyCallback;

	public:
		NRenderable();
		virtual void Draw(){};

		// Called on Renderable Draw. Shader doesn't have to be enabled to change uniforms
		void PropertyCallback()
		{
			if (m_PropertyCallback)
				propCb(this->Shader);
		}

		// Called on Renderable Draw. Shader doesn't have to be enabled to change uniforms
		void SetPropertyCallback(void (*ptr)(NShader*))
		{
			m_PropertyCallback = true;
			propCb = ptr;
		}
	};
}