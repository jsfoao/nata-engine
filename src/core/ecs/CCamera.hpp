#pragma once
#include "core/core.h"
#include "ecs.h"
#include "core/glm_math.h"

namespace Nata
{
	class CCamera : public CComponent
	{
	private:
		mat4 m_Projection;
		mat4 m_View;
		float m_Fov;
		float m_Near;
		float m_Far;

	public:
		CCamera() : CComponent()
		{
			m_View = mat4(1.f);
			m_Projection = mat4(1.f);
			m_Fov = 45.f;
			m_Near = 0.1f;
			m_Far = 100.f;
		}

		void Tick(float deltaTime) override
		{
			vec3 camPos = m_Owner->Transform->Position;
			vec3 camRotation = m_Owner->Transform->Rotation;

			// view and projection matrices
			m_Projection = perspective(radians(m_Fov), NEngine::WindowSizeX / NEngine::WindowSizeY, m_Near, m_Far);

			// camera
			vec3 camForward;
			float yaw = radians(camRotation.y);
			float pitch = radians(camRotation.x);

			camForward.x = cos(yaw) * cos(pitch);
			camForward.y = sin(pitch);
			camForward.z = sin(yaw) * cos(pitch);
			camForward = normalize(camForward);
			vec3 camRight = normalize(cross(vec3(0.f, 1.f, 0.f), camForward));
			vec3 camUp = cross(camForward, camRight);
			m_View = lookAt(camPos, camPos + camForward, camUp);
		}

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