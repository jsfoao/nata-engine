#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cmath>

using namespace glm;

namespace Math
{
	vec3 Lerp(vec3 start, vec3 end, float a);
	vec2 Lerp(vec2 start, vec2 end, float a);
	float Lerp(float start, float end, float a);

	vec3 MoveTowards(vec3 start, vec3 end, float maxDelta);
	float MoveTowards(float start, float end, float maxDelta);

	float Random(float min, float max);
	vec3 Random(vec3 min, vec3 max);
	vec2 Random(vec2 min, vec2 max);
}