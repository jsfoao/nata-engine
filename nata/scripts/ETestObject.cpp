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
}

void ETestObject::Begin()
{
}

void ETestObject::Tick(float dt)
{
	if (InputEnabled)
	{
		Movement(dt);
	}
	// IN: Original positions, original normals, Transform;
	// OUT: Transformed positions and unique normals
	Positions.clear();
	Normals.clear();
	std::vector<vec3> normals;
	NModel* renderable = (NModel*)ModelRendererComp->GetRenderable();
	mat4 model = mat4(1.f);
	for (unsigned int i = 0; i < renderable->Meshes[0].Vertices.size(); i++)
	{
		auto& vert = renderable->Meshes[0].Vertices[i];
		
		model = mat4(1.f);
		model = glm::translate(model, Transform->Position);
		model = glm::scale(model, Transform->Scale / 2.f);
		model = glm::rotate(model, radians(Transform->Rotation.x), vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, radians(Transform->Rotation.y), vec3(0.f, 1.f, 0.f));
		model = glm::rotate(model, radians(Transform->Rotation.z), vec3(0.f, 0.f, 1.f));
		
		// Transformed position
		vec3 position = model * vec4(vert.Position, 0.f);
		Positions.push_back(Transform->Position + position);

		// Normals
		bool exists = false;
		vec3 absNormal = AbsVec(vert.Normal);
		for (vec3 n : normals)
		{
			if (absNormal == n)
			{
				exists = true;
				break;
			}
		}
		if (!exists)
		{
			normals.push_back(absNormal);
		}
		
		Handles::DrawWireSphere(Transform->Position + position, 0.1f, vec3(1.f));
	}

	for (vec3 n1 : normals)
	{
		vec3 transfNormal = model * vec4(n1, 0.f);
		transfNormal = glm::normalize(transfNormal);
		Normals.push_back(transfNormal);
		Handles::DrawLine(Transform->Position, Transform->Position + transfNormal * 1.f, vec3(1.f));
	}

	//if (Target == nullptr)
	//{
	//	return;
	//}

	// Testing both objects normals
	bool overlap = false;
	std::vector<vec3> axes;
	//for (vec3 n : Target->Normals)
	//{
	//	axes.push_back(n);
	//}
	for (vec3 n1 : Normals)
	{
		axes.push_back(n1);
		//for (vec3 n2 : Target->Normals)
		//{
		//	axes.push_back(glm::cross(n1, n2));
		//}
	}

	for (vec3 ax : axes)
	{
		std::tuple<NRange, vec3, vec3> r1 = RangeScalarProjection(Positions, ax);
		NRange range1 = std::get<0>(r1);

		vec3 min = std::get<1>(r1);
		vec3 max = std::get<2>(r1);

		float proj = glm::dot(min, glm::normalize(ax));
		Handles::DrawWireSphere(proj * glm::normalize(ax), 0.15f, vec3(1.f, 0.f, 0.f));
		Handles::DrawLine(vec3(0.f), proj * glm::normalize(ax), vec3(1.f));

		proj = glm::dot(max, glm::normalize(ax));
		Handles::DrawWireSphere(proj * glm::normalize(ax), 0.15f, vec3(0.f, 1.f, 0.f));
		Handles::DrawLine(vec3(0.f), proj * glm::normalize(ax), vec3(1.f));
	}
}

void ETestObject::Movement(float dt)
{
	vec2 input;
	input.x = NEngine::Input->GetKeyHold(GLFW_KEY_D) - NEngine::Input->GetKeyHold(GLFW_KEY_A);
	input.y = NEngine::Input->GetKeyHold(GLFW_KEY_W) - NEngine::Input->GetKeyHold(GLFW_KEY_S);
	Transform->Position += vec3(input.x, 0.f, -input.y) * 3.f * dt;
}

float ETestObject::ScalarProjection(vec3 pos, vec3 axis)
{
	return glm::dot(pos, axis);
}

std::tuple<NRange, vec3, vec3> ETestObject::RangeScalarProjection(std::vector<vec3> positions, vec3 axis)
{
	float min = 99999.f;
	float max = 0.f;
	vec3 posMin = vec3(0.f);
	vec3 posMax = vec3(0.f);
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		float scalarProj = ScalarProjection(positions[i], axis);
		if (scalarProj < min)
		{
			min = scalarProj;
			posMin = positions[i];
		}
	}

	for (unsigned int i = 0; i < positions.size(); i++)
	{
		float scalarProj = ScalarProjection(positions[i], axis);
		if (scalarProj > max)
		{
			max = scalarProj;
			posMax = positions[i];
		}
	}
	return std::make_tuple(NRange(min, max), posMin, posMax);
}

bool ETestObject::IntersectRange(const NRange& r1, const NRange& r2)
{
	return r1.Min <= r2.Max && r1.Max >= r2.Min;
}

vec3 ETestObject::AbsVec(vec3 v)
{
	v.x = std::abs(v.x);
	v.y = std::abs(v.y);
	v.z = std::abs(v.z);
	return v;
}