#pragma once
#include "ecs/ecs.h"
#include "ecs/dots.h"
#include "nata_math.h"
#include <queue>

namespace Nata
{
	class NDAsteroidPool : public NDComponentPool
	{
	public:
		NWorld* world;
		NDComponent<CTransform> Transform;
		NDComponent<CTransform> TransformDelta;
		NDComponent<CModelRenderer> ModelRenderer;
		NDComponent<CBoxCollider> BoxCollider;
		vec3 Color;
		NModel* Model;
		NShader* Shader;
		float MinMoveSpeed;
		float MaxMoveSpeed;
		float MinRotationSpeed;
		float MaxRotationSpeed;
		float ZLimit;

		std::queue<unsigned int> DisabledIDs;

		NDAsteroidPool(unsigned int size) : NDComponentPool(size)
		{
			MinMoveSpeed = 5.f;
			MaxMoveSpeed = 15.f;
			MinRotationSpeed = 50.f;
			MaxRotationSpeed = 100.f;
			ZLimit = 40.f;
			Model = NAssetLoader::Get<NModel>("res\\models\\rock_by_dommk.obj");
			Shader = NAssetLoader::Get<NShader>("res\\shaders\\diffuse.vert");
			Color = vec3(0.5f);

			for (unsigned int i = 0; i < 6; i++)
			{
				Transform.Init(Size);
				TransformDelta.Init(Size);
				ModelRenderer.Init(size);
				BoxCollider.Init(Size);
			}
		}

		void Begin()
		{
			for (unsigned int i = 0; i < Size; i++)
			{
				float scale = Math::Random(0.03f, 0.08f);
				Transform[i].Position = vec3(0.f, 0.f, -75.f);
				Transform[i].Rotation = vec3(0.f);
				Transform[i].Scale = scale * vec3(1.f);

				float moveSpeed = Math::Random(MinMoveSpeed, MaxMoveSpeed);
				float rotationSpeed = Math::Random(MinRotationSpeed, MaxRotationSpeed);
				vec3 randomAxis = Math::Random(vec3(-1.f), vec3(1.f));
				TransformDelta[i].Position = moveSpeed * vec3(0.f, 0.f, 1.f);
				TransformDelta[i].Rotation = rotationSpeed * randomAxis;
				TransformDelta[i].Scale = vec3(0.f);

				BoxCollider[i].LockOwner = false;
				BoxCollider[i].Bounds = Transform[i].Scale * 80.f;

				ModelRenderer[i].SetRenderableAndShader(Model, Shader);
				ModelRenderer[i].PropertyLayout.AddVec3("color");
				ModelRenderer[i].PropertyLayout.SetVec3("color", vec3(0.9f, 0.9f, 0.9f));
			}
		}

		void Tick(float dt)
		{
			while (!DisabledIDs.empty())
			{
				unsigned int id = DisabledIDs.front();
				BoxCollider[id].m_Overlaps.clear();
				DisableID(id);
				DisabledIDs.pop();
			}

			for (auto& id : m_Enabled)
			{
				Transform[id].Position += TransformDelta[id].Position * dt;
				Transform[id].Rotation += TransformDelta[id].Rotation * dt;
				Transform[id].Scale += TransformDelta[id].Scale;

				// collisions
				BoxCollider[id].Position = Transform[id].Position;

				vec3 hBound = BoxCollider[id].Bounds / 2.f;
				NBox box = NBox(
					NRange(BoxCollider[id].Position.x - hBound.x, BoxCollider[id].Position.x + hBound.x),
					NRange(BoxCollider[id].Position.y - hBound.y, BoxCollider[id].Position.y + hBound.y),
					NRange(BoxCollider[id].Position.z - hBound.z, BoxCollider[id].Position.z + hBound.z)
				);

				bool disabled = false;
				std::vector<CBoxCollider*> boxColliders = GetAllComponentsOfType<CBoxCollider>(world);
				for (CBoxCollider* collider : boxColliders)
				{
					if (collider->IsEnable() == false)
					{
						continue;
					}
					if (Intersect(box, collider->GetBox()))
					{
						disabled = true;

						EProjectile* proj = dynamic_cast<EProjectile*>(collider->GetOwner());
						if (proj != nullptr)
						{
							proj->ProjectilePool->Delete(proj);
						}

						EShip* ship = dynamic_cast<EShip*>(collider->GetOwner());
						if (ship != nullptr)
						{
							ship->Transform->Position = vec3(0.f);
							Clear();
						}
						break;
					}
				}
				//Handles::DrawWireCube(Transform[id].Position, BoxCollider[id].Bounds, vec3(1.f, 0.f, 0.f));

				// rendering
				ModelRenderer[id].Position = Transform[id].Position;
				ModelRenderer[id].Rotation = Transform[id].Rotation;
				ModelRenderer[id].Scale = Transform[id].Scale;

				NShader* shader = ModelRenderer[id].GetRenderable()->Shader;
				NEngine::Window->GetRenderer()->Submit(&ModelRenderer[id]);
				
				if (disabled)
				{
					DisabledIDs.push(id);
				}
			}
		}

		void Clear()
		{
			for (auto& id : m_Enabled)
			{
				DisabledIDs.push(id);
			}
		}
	};
}