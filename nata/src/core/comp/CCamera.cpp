#include "CCamera.h"

namespace Nata
{
	INIT_COMPONENT(CCamera);

	CCamera::CCamera() : CSpatialComponent()
	{
		m_View = mat4(1.f);
		m_Projection = mat4(1.f);
		m_Fov = 45.f;
		m_Near = 0.1f;
		m_Far = 150.f;
		Name = "Camera";
	}

	void CCamera::Begin()
	{
		Transform = m_Owner->Transform;
	}

	void CCamera::Tick(float deltaTime)
	{
		// view and projection matrices
		m_Projection = perspective(radians(m_Fov), (float)NEngine::WindowSizeX / (float)NEngine::WindowSizeY, m_Near, m_Far);

		// camera
		vec3 camForward;
		float yaw = radians(Transform->Rotation.y);
		float pitch = radians(Transform->Rotation.x);

		camForward.x = cos(yaw) * cos(pitch);
		camForward.y = sin(pitch);
		camForward.z = sin(yaw) * cos(pitch);
		camForward = normalize(camForward);
		vec3 camRight = normalize(cross(vec3(0.f, 1.f, 0.f), camForward));
		vec3 camUp = cross(camForward, camRight);
		m_View = lookAt(Transform->Position, Transform->Position + camForward, camUp);
	}
}