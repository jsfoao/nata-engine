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
		Transform->Rotation += vec3(0.f, 1.f, 0.5f) * 45.f * dt;
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
		Handles::DrawLine(Transform->Position, Transform->Position + n * 2.f, vec3(0.f, 0.f, 1.f));
	}

	if (IntersectSAT(Shape, Target->Shape))
	{
		ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f, 0.f, 0.f));
	}
	else
	{
		ModelRendererComp->PropertyLayout.SetVec3("color", vec3(1.f));
	}

	NBox box = Shape.GetBoundingBox();

	const vec3 color = vec3(0.f, 1.f, 0.f);

	//Handles::DrawLine(vec3(0.f), vec3(box.RangeX.Max, 0.f, 0.f), color);

	vec3 v0 = vec3(box.RangeX.Min, box.RangeY.Min, box.RangeZ.Min);
	vec3 v1 = vec3(box.RangeX.Max, box.RangeY.Min, box.RangeZ.Min);
	vec3 v2 = vec3(box.RangeX.Max, box.RangeY.Min, box.RangeZ.Max);
	vec3 v3 = vec3(box.RangeX.Min, box.RangeY.Min, box.RangeZ.Max);

	vec3 v4 = vec3(box.RangeX.Min, box.RangeY.Max, box.RangeZ.Min);
	vec3 v5 = vec3(box.RangeX.Max, box.RangeY.Max, box.RangeZ.Min);
	vec3 v6 = vec3(box.RangeX.Max, box.RangeY.Max, box.RangeZ.Max);
	vec3 v7 = vec3(box.RangeX.Min, box.RangeY.Max, box.RangeZ.Max);

	Handles::DrawLine(v0, v1, color);
	Handles::DrawLine(v1, v2, color);
	Handles::DrawLine(v2, v3, color);
	Handles::DrawLine(v3, v0, color);
	
	Handles::DrawLine(v4, v5, color);
	Handles::DrawLine(v5, v6, color);
	Handles::DrawLine(v6, v7, color);
	Handles::DrawLine(v7, v4, color);
	
	Handles::DrawLine(v0, v4, color);
	Handles::DrawLine(v1, v5, color);
	Handles::DrawLine(v2, v6, color);
	Handles::DrawLine(v3, v7, color);
}

void ETestObject::Movement(float dt)
{
	vec2 input;
	input.x = NEngine::Input->GetKeyHold(GLFW_KEY_D) - NEngine::Input->GetKeyHold(GLFW_KEY_A);
	input.y = NEngine::Input->GetKeyHold(GLFW_KEY_W) - NEngine::Input->GetKeyHold(GLFW_KEY_S);
	Transform->Position += vec3(input.x, 0.f, -input.y) * 3.f * dt;
}