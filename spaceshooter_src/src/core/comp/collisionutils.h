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

		NBox() {}

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
		float Radius;

		NSphere();
		NSphere(vec3 position, float radius);
	};

	bool IsPointInsideAABB(vec3 point, NBox box);
	bool IsPointInsideSphere(vec3 point, NSphere sphere);
	bool Intersect(NBox a, NBox b);
	bool Intersect(NSphere a, NSphere b);
	bool Intersect(NSphere s, NBox b);
}