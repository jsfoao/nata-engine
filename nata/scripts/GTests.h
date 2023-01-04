#pragma once
#include "nata.h"
#include "comp/ECamera.hpp"
#include "ETestObject.h"

class GTests : public GGameMode
{
public:
	ETestObject* object;

public:
	void Begin() override;
	void Tick(float dt) override;
};