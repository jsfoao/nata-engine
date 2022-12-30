#include "EFollowCamera.h"

namespace Nata
{
	EFollowCamera::EFollowCamera() : EEntity()
	{
		CameraComp = AddComponent<CCamera>();
		Target = nullptr;
		Speed = 1.f;
		BoomDistance = 20.f;
		CenterMaxDistance = 1.f;
		Transform->Rotation = vec3(0.f, -90.f, 0.f);
	}

	void EFollowCamera::Begin()
	{

	}

	void EFollowCamera::Tick(float dt)
	{
		vec3 targetPos = vec3(0.f);
		if (Target != nullptr)
		{
			targetPos = Target->Transform->Position;
		}
		vec2 xyPos = vec2(Transform->Position.x, Transform->Position.y);
		vec2 xyTargetPos = vec2(targetPos.x, targetPos.y);
		if (glm::length(xyTargetPos) > CenterMaxDistance)
		{
			xyTargetPos = glm::normalize(xyTargetPos) * CenterMaxDistance;
		}
		vec2 newPos = Math::Lerp(xyPos, xyTargetPos, Speed * dt);
		Transform->Position = vec3(newPos.x, newPos.y, BoomDistance);

		Handles::DrawLine(vec3(0.f), vec3(xyTargetPos.x, xyTargetPos.y, 0.f), vec3(1.f, 0.f, 0.f));
	}
}