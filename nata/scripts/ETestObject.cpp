#include "ETestObject.h"

ETestObject::ETestObject() : EEntity()
{
	ModelRendererComp = AddComponent<CModelRenderer>();

	//NModel* model = NAssetLoader::Get<NModel>(")
	//ModelRendererComp->SetRenderableAndShader()
}

void ETestObject::Begin()
{
}

void ETestObject::Tick(float dt)
{
}
