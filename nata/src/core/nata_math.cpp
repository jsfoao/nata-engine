#include "nata_math.h"

namespace Math
{
	vec3 Lerp(vec3 start, vec3 end, float a)
	{
		return (start + a * (end - start));
	}

	vec2 Lerp(vec2 start, vec2 end, float a)
	{
		return (start + a * (end - start));
	}

	float Lerp(float start, float end, float a)
	{
		return (start + a * (end - start));
	}

	vec3 MoveTowards(vec3 current, vec3 target, float maxDelta)
	{
		vec3 a = target - current;
		float magnitude = glm::length(a);
		if (magnitude <= maxDelta || magnitude == 0.f)
		{
			return target;
		}
		return current + a / magnitude * maxDelta;
	}

	float MoveTowards(float start, float end, float maxDelta)
	{
		if (glm::abs(end - start) <= maxDelta)
		{
			return end;
		}
		return start + glm::sign(end - start) * maxDelta;
	}

	float Random(float min, float max)
	{
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

	vec3 Random(vec3 min, vec3 max)
	{
		float fx = min.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.x - min.x)));
		float fy = min.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.y - min.y)));
		float fz = min.z + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.z - min.z)));
		return vec3(fx, fy, fz);
	}

	vec2 Random(vec2 min, vec2 max)
	{
		float fx = min.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.x - min.x)));
		float fy = min.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.y - min.y)));
		return vec2(fx, fy);
	}
	vec3 Abs(vec3 v)
	{
		vec3 temp = vec3(0.f);
		if (v != vec3(0.f))
		{
			temp.x = std::abs(v.x);
			temp.y = std::abs(v.y);
			temp.z = std::abs(v.z);
		}
		return temp;
	}
}
