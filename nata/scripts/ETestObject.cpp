#include "ETestObject.h"

ETestObject::ETestObject() : EEntity()
{
	Name = "TestObject";
	//BoxColliderComp = AddComponent<CBoxCollider>();
	//BoxColliderComp->DrawHandles = true;
	//BoxColliderComp->Transform->Scale = vec3(1.f);

	ModelRendererComp = AddComponent<CModelRenderer>();
	NModel* model = NAsset::Get<NModel>("res\\assets\\CubeTest");
	NShader* shader = NAsset::Get<NShader>("res\\assets\\DiffuseShader");
	ModelRendererComp->SetRenderableAndShader(model, shader);
	ModelRendererComp->PropertyLayout.AddVec3("color");
	ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f));

	InputEnabled = false;

	for (unsigned int i = 0; i < model->Meshes[0].Vertices.size(); i++)
	{
		Shape.AddPosition(model->Meshes[0].Vertices[i].Position);
		Shape.AddNormal(model->Meshes[0].Vertices[i].Normal);
	}
}

void ETestObject::Begin()
{
}

void ETestObject::Tick(float dt)
{
	if (InputEnabled)
	{
		Transform->Rotation += vec3(0.f, 1.f, 0.f) * 45.f * dt;
		Movement(dt);
	}

	Shape.Position = Transform->Position;
	Shape.Rotation = Transform->Rotation;
	Shape.Scale = Transform->Scale;
	for (vec3 v : Shape.GetTransformedPos())
	{
		Handles::DrawWireSphere(v, 0.15f, vec3(1.f, 0.f, 0.f));
	}

	for (vec3 n : Shape.GetEdgeNormals())
	{
		Handles::DrawLine(Transform->Position, Transform->Position + n, vec3(0.f, 0.f, 1.f));
	}

	if (IntersectSAT(Shape, Target->Shape))
	{
		ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f, 0.f, 0.f));
	}
	else
	{
		ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f));
	}

	//NBox box = Shape.GetBoundingBox();

}

void ETestObject::Movement(float dt)
{
	vec2 input;
	input.x = NEngine::Input->GetKeyHold(GLFW_KEY_D) - NEngine::Input->GetKeyHold(GLFW_KEY_A);
	input.y = NEngine::Input->GetKeyHold(GLFW_KEY_W) - NEngine::Input->GetKeyHold(GLFW_KEY_S);
	Transform->Position += vec3(input.x, 0.f, -input.y) * 3.f * dt;
}