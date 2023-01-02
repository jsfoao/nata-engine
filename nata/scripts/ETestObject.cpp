#include "ETestObject.h"

ETestObject::ETestObject() : EEntity()
{
	Name = "TestObject";
	BoxColliderComp = AddComponent<CBoxCollider>(false);
	BoxColliderComp->DrawHandles = true;
	BoxColliderComp->LockPosition = true;
	BoxColliderComp->Transform->Scale = vec3(2.f);

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
	Debug::Log(this);
}

void ETestObject::Tick(float dt)
{
	Transform->Rotation += vec3(0.f, 90.f, 0.f) * dt;
	Handles::DrawHandles(BoxColliderComp->Transform, 2.f);

	if (NEngine::Input->GetKeyDown(GLFW_KEY_SPACE))
	{
		BoxColliderComp->Super_SetEnable(true);
		Debug::Log(this);
	}

}
