#include "ETestObject.h"

ETestObject::ETestObject() : EEntity()
{
	ModelRendererComp = AddComponent<CModelRenderer>();

	NModel* model = NAsset::Get<NModel>("res\\assets\\CubeTest");
	NShader* shader = NAsset::Get<NShader>("res\\assets\\DiffuseShader");
	ModelRendererComp->SetRenderableAndShader(model, shader);
	ModelRendererComp->PropertyLayout.AddVec3("color");
	ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f));
	Transform->Scale = vec3(1.f);
}

void ETestObject::Begin()
{
}

void ETestObject::Tick(float dt)
{
	Transform->Rotation += vec3(0.f, 90.f, 0.f) * dt;
}
