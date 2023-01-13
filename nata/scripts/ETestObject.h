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
	std::vector<vec3> Vertices;
	std::vector<vec3> Normals;

	ETestObject* Target;
	NShape Shape;

public:
	ETestObject();
	void Begin() override;
	void Tick(float dt) override;
	void Movement(float dt);
};