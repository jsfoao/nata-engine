#include "collisionutils.h"

namespace Nata
{
	NSphere::NSphere(vec3 position, float radius)
	{
		Position = position;
		Radius = radius;
	}

	NSphere::NSphere()
	{
		Position = vec3(0.f);
		Radius = 1.f;
	}

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
		vec3 dir = point - sphere.Position;
		float dist = glm::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		return dist < sphere.Radius;
	}

	bool Intersect(NBox a, NBox b)
	{
		return
			a.RangeX.Min <= b.RangeX.Max &&
			a.RangeX.Max >= b.RangeX.Min &&
			a.RangeY.Min <= b.RangeY.Max &&
			a.RangeY.Max >= b.RangeY.Min &&
			a.RangeZ.Min <= b.RangeZ.Max &&
			a.RangeZ.Max >= b.RangeZ.Min;
	}

	bool Intersect(NSphere a, NSphere b)
	{
		vec3 dir = a.Position - b.Position;
		float dist = glm::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		return dist < a.Radius * 2 + b.Radius * 2;
	}

	bool Intersect(NSphere s, NBox b)
	{
		float x = glm::max(b.RangeX.Min, glm::min(s.Position.x, b.RangeX.Max));
		float y = glm::max(b.RangeY.Min, glm::min(s.Position.y, b.RangeY.Max));
		float z = glm::max(b.RangeZ.Min, glm::min(s.Position.z, b.RangeZ.Max));
		vec3 dir = vec3(x, y, z) - s.Position;
		float dist = glm::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		return dist < s.Radius;
	}
}