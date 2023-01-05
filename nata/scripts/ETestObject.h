#pragma once
#include "nata.h"
#include "comp/CModelRenderer.h"
#include "comp/CBoxCollider.h"
#include <tuple>

class ETestObject : public EEntity
{
public:
	CModelRenderer* ModelRendererComp;
	CBoxCollider* BoxColliderComp;
	bool InputEnabled;
	
	// Transformed
	std::vector<vec3> Positions;
	std::vector<vec3> Normals;

	ETestObject* Target;

public:
	ETestObject();
	void Begin() override;
	void Tick(float dt) override;
	void Movement(float dt);
	float ScalarProjection(vec3 pos, vec3 axis);
	std::tuple<NRange, vec3, vec3> RangeScalarProjection(std::vector<vec3> positions, vec3 axis);
	bool IntersectRange(const NRange& r1, const NRange& r2);
	vec3 AbsVec(vec3 v);
};