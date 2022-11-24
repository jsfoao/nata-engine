#pragma once
#include "core/glm_math.h"
#include <iostream>

namespace Nata
{
	struct Rotator
	{
		float Yaw;
		float Pitch;
		float Roll;

		Rotator()
		{
			Yaw = 0.f;
			Pitch = 0.f;
			Roll = 0.f;
		}

		Rotator(float yaw, float pitch, float roll)
		{
			this->Yaw = yaw;
			this->Pitch = pitch;
			this->Roll = roll;
		}

		Rotator(float value)
		{
			this->Yaw = value;
			this->Pitch = value;
			this->Roll = value;
		}
	};

	// default camera values
	const float YAW = -90.f;
	const float PITCH = 0.f;
	const float ROLL = 0.f;
	const float SPEED = 5.f;
	const float SENSITIVITY = 0.75f;
	const float ZOOM = 1.f;

	class Camera
	{
	public:
		// transform position
		vec3 Position;
		vec3 Front;
		vec3 Up;
		vec3 Right;

		vec3 WorldUp;

		// transform rotation (euler angles)
		Rotator Rotation;
		// move options
		float Speed;
		float Sensitivity;
		float Zoom;

	public:
		Camera(vec3 position = vec3(0.f), vec3 up = vec3(0.f, 1.f, 0.f), Rotator rotation = Rotator(PITCH, YAW, ROLL));
		
		void Tick();
		mat4 GetViewMatrix();

	private:
		// calculates front camera from camera's updated euler angles
		void UpdateCameraVectors();
	};
}