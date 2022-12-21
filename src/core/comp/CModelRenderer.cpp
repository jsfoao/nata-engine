#include "CModelRenderer.h"

namespace Nata
{
	INIT_COMPONENT(CModelRenderer);

	CModelRenderer::CModelRenderer() : CComponent()
	{
		INIT_ID(CModelRenderer);
		m_Shader = nullptr;
		m_Texture = nullptr;
		m_Model = nullptr;
		m_IsVisible = true;
		Position = vec3(0.f);
		Rotation = vec3(0.f);
		Scale = vec3(0.f);
	}

	void CModelRenderer::Init(NShader* shader, NModel* model, NTexture* texture)
	{
		m_Shader = shader;
		m_Texture = texture;
		m_Model = model;
		model->Shader = m_Shader;
		model->PropertyLayout.Bind(m_Shader);
		m_IsVisible = true;
	}

	void CModelRenderer::Tick(float dt)
	{
		SuperTick(dt);
		if (!m_IsVisible)
		{
			return;
		}
		m_Model->Position = m_Owner->Transform->Position + Position;
		m_Model->Scale = m_Owner->Transform->Scale + Scale;
		m_Model->Rotation = m_Owner->Transform->Rotation + Rotation;
		NEngine::Window->GetRenderer()->Submit(m_Model);
	}
}