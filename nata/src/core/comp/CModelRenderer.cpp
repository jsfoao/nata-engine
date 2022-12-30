#include "CModelRenderer.h"

namespace Nata
{
	INIT_COMPONENT(CModelRenderer);

	CModelRenderer::CModelRenderer() : CComponent(), NRenderable()
	{
		INIT_ID(CModelRenderer);
		m_IsVisible = true;
		LocalPosition = vec3(0.f);
		LocalRotation = vec3(0.f);
		LocalScale = vec3(0.f);
		m_Renderable = nullptr;
	}

	void CModelRenderer::SetRenderableAndShader(NRenderable* renderable, NShader* shader)
	{
		Shader = shader;
		m_Renderable = renderable;
		m_Renderable->Shader = Shader;
		PropertyLayout.Bind(Shader);
	}

	void CModelRenderer::Tick(float dt)
	{
		if (!m_IsVisible)
		{
			return;
		}
		Position = m_Owner->Transform->Position + LocalPosition;
		Scale = m_Owner->Transform->Scale + LocalScale;
		Rotation = m_Owner->Transform->Rotation + LocalRotation;
		NEngine::Window->GetRenderer()->Submit(this);
	}

	void CModelRenderer::Draw()
	{
		m_Renderable->Position = Position;
		m_Renderable->Scale = Scale;
		m_Renderable->Rotation = Rotation;
		PropertyLayout.SetProperties();
		m_Renderable->Draw();
	}
}