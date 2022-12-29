#include "CCamera.h"

namespace Nata
{
	INIT_COMPONENT(CCamera);

	CCamera::CCamera() : CComponent()
	{
		INIT_ID(CCamera);
		m_View = mat4(1.f);
		m_Projection = mat4(1.f);
		m_Fov = 45.f;
		m_Near = 0.1f;
		m_Far = 150.f;
	}

	void CCamera::Tick(float deltaTime)
	{
		vec3 camPos = m_Owner->Transform->Position;
		vec3 camRotation = m_Owner->Transform->Rotation;

		// view and projection matrices
		m_Projection = perspective(radians(m_Fov), (float)NEngine::WindowSizeX / (float)NEngine::WindowSizeY, m_Near, m_Far);

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
}