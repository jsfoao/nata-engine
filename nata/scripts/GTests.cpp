#include "GTests.h"

void GTests::Begin()
{
	NEngine::Camera = Instantiate<ECamera>(GetWorld())->Camera;
	NEngine::Camera->GetOwner()->Transform->Position = vec3(0.f, 0.f, 10.f);
	Instantiate<ETestObject>(GetWorld());
}

void GTests::Tick(float dt)
{
}
