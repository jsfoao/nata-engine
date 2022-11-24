#include "camera.h"

namespace Nata
{
	Camera::Camera(vec3 position, vec3 up, Rotator rotation)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Rotation = rotation;
		this->UpdateCameraVectors();
	}

	void Camera::Tick()
	{
		// camera behaviour, movement and such
	}

	mat4 Camera::GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	void Camera::UpdateCameraVectors()
	{
		// forward vector
		vec3 forward;
		forward.x = cos(Rotation.Yaw) * cos(Rotation.Pitch);
		forward.y = sin(Rotation.Yaw);
		forward.z = sin(Rotation.Yaw) * cos(Rotation.Pitch);
		forward = normalize(forward);

		// right vector
		vec3 right = normalize(cross(vec3(0.f, 1.f, 0.f), forward));

		// up vector
		vec3 up = cross(forward, right);
	}
}
