#pragma once
#include "nata.h"
#include "comp/CModelRenderer.h"
#include "comp/CBoxCollider.h"

class ETestObject : public EEntity
{
public:
	CModelRenderer* ModelRendererComp;
	CBoxCollider* BoxColliderComp;
	bool Enable;

public:
	ETestObject();
	void Begin() override;
	void Tick(float dt) override;
};