#pragma once
#include "nata.h"
#include "comp/ECamera.hpp"
#include "ETestObject.h"

class GTests : public GGameMode
{
public:
	void Begin() override;
	void Tick(float dt) override;
};