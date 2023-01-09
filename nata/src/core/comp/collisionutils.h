#pragma once
#include <vector>
#include "ecs/ecs.h"
#include "nata_math.h"

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
	
	struct NShape
	{
		std::vector<vec3> Vertices;
		std::vector<vec3> Normals;
		vec3 Position;
		vec3 Rotation;
		vec3 Scale;


		NShape();
		NShape(vec3 rot, vec3 scale);
		NShape(std::vector<vec3> positions, std::vector<vec3> normals, vec3 rot, vec3 scale);

		void AddPosition(vec3 pos);
		void AddNormal(vec3 norm);
		
		mat4 GetModel();
		std::vector<vec3> GetTransformedPos();
		std::vector<vec3> GetEdgeNormals();
		//NBox GetBoundingBox();
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
	bool IntersectSAT(NShape& s1, NShape& s2);
	bool RangesOverlap(NRange r1, NRange r2);
	NRange MinMaxScalarProjection(std::vector<vec3> positions, vec3 axis);
}