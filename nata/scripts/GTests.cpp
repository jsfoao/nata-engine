#include "GTests.h"

void GTests::Begin()
{
	NEngine::Camera = Instantiate<ECamera>(GetWorld())->Camera;
	NEngine::Camera->GetOwner()->Transform->Position = vec3(0.f, 0.f, 10.f);
	object = Instantiate<ETestObject>(GetWorld(), false);
	Debug::Log(object);
}

void GTests::Tick(float dt)
{
	if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
	{
		object->ModelRendererComp->SetEnable(false);
		Debug::Log(object);
	}
	if (NEngine::Input->GetKeyDown(GLFW_KEY_S))
	{
		object->SetEnable(true);
	}
}
