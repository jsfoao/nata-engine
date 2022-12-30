#pragma once
#include "core/core.h"
#include "core/ecs/ecs.h"
#include "core/glm_math.h"

namespace Nata
{
	class CCamera : public CComponent
	{
		GENERATE_COMPONENT;
	private:
		mat4 m_Projection;
		mat4 m_View;
		float m_Fov;
		float m_Near;
		float m_Far;

	public:
		CCamera();

		void Tick(float deltaTime) override;

		inline void SetFov(float fov)
		{
			m_Fov = fov;
		}

		inline void SetNear(float near)
		{
			m_Near = near;
		}

		inline void SetFar(float far)
		{
			m_Far = far;
		}

		inline mat4 GetProjectionMatrix()
		{
			return m_Projection;
		}

		inline mat4 GetViewMatrix()
		{
			return m_View;
		}
	};
}