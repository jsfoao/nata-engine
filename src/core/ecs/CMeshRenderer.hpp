#pragma once
#include "nata.h"

namespace Nata
{
	class NWindow;
	class CModelRenderer : public CComponent
	{
	protected:
		NShader* m_Shader;
		NTexture* m_Texture;
		NModel* m_Model;

	public:
		void SetAll(NShader* shader, NModel* model, NTexture* texture = nullptr)
		{
			m_Shader = shader;
			m_Texture = texture;
			m_Model = model;
			model->Shader = m_Shader;
		}

		NShader* GetShader()
		{
			return m_Shader;
		}
		
		void Tick(float dt) override
		{
			m_Model->Position = m_Owner->Transform->Position;
			m_Model->Scale = m_Owner->Transform->Scale;
			m_Model->Rotation = m_Owner->Transform->Rotation;
			NWindow* window = NEngine::Window;
			window->GetRenderer()->Submit(m_Model);
		}
	};
}