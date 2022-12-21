#pragma once
#include "nata.h"
#include "core/comp/CCamera.h"

namespace Nata
{
	class EFollowCamera : public EEntity
	{
	public:
		CCamera* CameraComp;
		EEntity* Target;
		float Speed;
		float BoomDistance;
		float CenterMaxDistance;

	public:
		EFollowCamera();
		void Begin() override;
		void Tick(float dt) override;
	};
}