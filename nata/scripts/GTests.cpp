#include "GTests.h"

void GTests::Begin()
{
	NEngine::Camera = Instantiate<ECamera>(GetWorld())->Camera;
}

void GTests::Tick(float dt)
{
}
