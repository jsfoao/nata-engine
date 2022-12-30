#pragma once
#include "nata.h"
#include "comp/CModelRenderer.h"

class ETestObject : public EEntity
{
public:
	CModelRenderer* ModelRendererComp;

public:
	ETestObject();
	void Begin() override;
	void Tick(float dt) override;
};