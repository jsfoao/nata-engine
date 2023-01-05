#include "GTests.h"

void GTests::Begin()
{
	NEngine::Camera = Instantiate<ECamera>(GetWorld())->Camera;
	ETestObject* obj1 = Instantiate<ETestObject>(GetWorld(), vec3(0.f, 2.f, 0.f), vec3(0.f, 0.f, 0.f));
	obj1->InputEnabled = true;
	ETestObject* obj2 = Instantiate<ETestObject>(GetWorld(), vec3(2.f, 2.f, 0.f), vec3(0.f));
	obj1->Target = obj2;
	obj2->Target = obj1;

	std::vector<EEntity*> entities = NWorld::Current->GetAllEntities();
	for (auto& entity : entities)
	{
		Debug::Log(entity);
	}
}

void GTests::Tick(float dt)
{
	//const int sizeX = 10;
	//const int sizeZ = 10;
	//const vec3 color = vec3(0.5f);

	//vec3 origin = vec3(-5.f, 0.f, -5.f);
	//Handles::DrawWireSphere(vec3(0.f), 0.1f, vec3(1.f));
	//float step = 1.f;
	//for (unsigned int x = 1; x <= sizeX; x++)
	//{
	//	for (unsigned int z = 1; z <= sizeZ; z++)
	//	{
	//		vec3 pos = origin + vec3(x, 0.f, z) * step;
	//		vec3 posX = origin + vec3(x - 1, 0.f, z) * step;
	//		vec3 posZ = origin + vec3(x, 0.f, z - 1) * step;
	//		Handles::DrawLine(pos, posX, color);
	//		Handles::DrawLine(pos, posZ, color);
	//	}
	//}

	//Handles::DrawLine(origin, origin + vec3(sizeX, 0.f, 0.f), color);
	//Handles::DrawLine(origin, origin + vec3(0.f, 0.f, sizeZ), color);
	//Handles::DrawLine(origin + vec3(0.f, 0.f, sizeZ), origin + vec3(sizeX, 0.f, sizeZ), color);
	//Handles::DrawLine(origin + vec3(sizeX, 0.f, sizeZ), origin + vec3(sizeX, 0.f, 0.f), color);
}