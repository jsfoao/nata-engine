#pragma once
#include "core/glm_math.h"

namespace Nata
{
	struct NRange
	{
		float Min;
		float Max;

		NRange()
		{
			Min = 0;
			Max = 0;
		}
		NRange(float min, float max)
		{
			Min = min;
			Max = max;
		}
	};

	struct NBox
	{
		NRange RangeX;
		NRange RangeY;
		NRange RangeZ;

		NBox(NRange rangeX, NRange rangeY, NRange rangeZ)
		{
			RangeX = rangeX;
			RangeY = rangeY;
			RangeZ = rangeZ;
		}
	};

	struct NSphere
	{
		vec3 Position;
		vec3 Radius;

		NSphere(vec3 position, vec3 radius)
		{
			Position = position;
			Radius = radius;
		}
	};

	bool IsPointInsideAABB(vec3 point, NBox box)
	{
		return
			point.x >= box.RangeX.Min &&
			point.x <= box.RangeX.Max &&
			point.y >= box.RangeY.Min &&
			point.y <= box.RangeY.Max &&
			point.z >= box.RangeZ.Min &&
			point.z <= box.RangeZ.Max;
	}

	bool IsPointInsideSphere(vec3 point, NSphere sphere)
	{

	}
}