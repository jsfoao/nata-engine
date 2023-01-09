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

	bool IntersectSAT(NShape& s1, NShape& s2)
	{
		std::vector<vec3> axes;
		bool pushed = false;
		for (vec3 n1 : s1.GetEdgeNormals())
		{
			axes.push_back(n1);
			for (vec3 n2 : s2.GetEdgeNormals())
			{
				if (!pushed)
				{
					axes.push_back(n2);
				}
				axes.push_back(glm::cross(n1, n2));
			}
			pushed = true;
		}

		std::vector<vec3> pos1 = s1.GetTransformedPos();
		std::vector<vec3> pos2 = s2.GetTransformedPos();
		for (vec3 axis : axes)
		{
			NRange r1 = MinMaxScalarProjection(pos1, axis);
			NRange r2 = MinMaxScalarProjection(pos2, axis);
			if (!RangesOverlap(r1, r2))
			{
				return false;
			}
		}
		return true;
	}

	bool RangesOverlap(NRange r1, NRange r2)
	{
		return r1.Min <= r2.Max && r1.Max >= r2.Min;
	}

	NRange MinMaxScalarProjection(std::vector<vec3> positions, vec3 axis)
	{
		float min = 99999.f;
		float max = 0.f;
		vec3 posMin = vec3(0.f);
		vec3 posMax = vec3(0.f);
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			float scalarProj = glm::dot(positions[i], axis);
			if (scalarProj < min)
			{
				min = scalarProj;
				posMin = positions[i];
			}
		}

		for (unsigned int i = 0; i < positions.size(); i++)
		{
			float scalarProj = glm::dot(positions[i], axis);
			if (scalarProj > max)
			{
				max = scalarProj;
				posMax = positions[i];
			}
		}
		return NRange(min, max);
	}

	NShape::NShape()
	{
		Rotation = vec3(0.f);
		Scale = vec3(1.f);
	}

	NShape::NShape(vec3 rot, vec3 scale)
	{
		Rotation = rot;
		Scale = scale;
	}

	NShape::NShape(std::vector<vec3> positions, std::vector<vec3> normals, vec3 rot, vec3 scale)
	{
		Vertices = positions;
		Normals = normals;
		Rotation = rot;
		Scale = scale;
	}

	void NShape::AddPosition(vec3 pos)
	{
		Vertices.push_back(pos);
	}

	void NShape::AddNormal(vec3 norm)
	{
		Normals.push_back(norm);
	}

	mat4 NShape::GetModel()
	{
		mat4 model = mat4(1.f);
		model = glm::translate(model, Position);
		model = glm::scale(model, Scale / 2.f);
		model = glm::rotate(model, radians(Rotation.x), vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, radians(Rotation.y), vec3(0.f, 1.f, 0.f));
		model = glm::rotate(model, radians(Rotation.z), vec3(0.f, 0.f, 1.f));
		return model;
	}

	std::vector<vec3> NShape::GetTransformedPos()
	{
		std::vector<vec3> transfPos;
		mat4 model = GetModel();
		for (vec3 pos : Vertices)
		{
			vec3 transformed = model * vec4(pos, 1.f);
			transfPos.push_back(transformed);
		}
		return transfPos;
	}

	std::vector<vec3> NShape::GetEdgeNormals()
	{
		std::vector<vec3> edgeNormals;
		for (vec3 normal : Normals)
		{
			bool exists = false;
			vec3 absNormal = Math::Abs(normal);
			for (vec3 edgeNormal : edgeNormals)
			{
				if (absNormal == edgeNormal)
				{
					exists = true;
					break;
				}
			}
			if (!exists)
			{
				edgeNormals.push_back(absNormal);
			}
		}

		for (vec3 n : edgeNormals)
		{
			n = glm::normalize(GetModel() * vec4(n, 1.f));
		}
		return edgeNormals;
	}

	NBox NShape::GetBoundingBox()
	{
		NBox box;
		box.RangeX = NRange(99999.f, 0.f);
		box.RangeY = NRange(99999.f, 0.f);
		box.RangeZ = NRange(99999.f, 0.f);
		for (vec3 pos : Vertices)
		{
			// mins
			if (pos.x < box.RangeX.Min)
			{
				box.RangeX.Min = pos.x;
			}
			if (pos.y < box.RangeY.Min)
			{
				box.RangeY.Min = pos.y;
			}
			if (pos.z < box.RangeZ.Min)
			{
				box.RangeZ.Min = pos.z;
			}

			// maxs
			if (pos.x > box.RangeX.Max)
			{
				box.RangeX.Max = pos.x;
			}
			if (pos.y > box.RangeY.Max)
			{
				box.RangeY.Max = pos.y;
			}
			if (pos.z > box.RangeZ.Max)
			{
				box.RangeZ.Max = pos.z;
			}
		}
		return box;
	}
}