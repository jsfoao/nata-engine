#include "renderer.h"

namespace Nata
{
	void NRenderer::Submit(NRenderable* renderable, bool flush)
	{
		if (flush)
		{
			NShader* shader = renderable->Shader;
			shader->Enable();
			shader->SetUniformMat4("view", NEngine::Camera->GetViewMatrix());
			shader->SetUniformMat4("projection", NEngine::Camera->GetProjectionMatrix());
			renderable->Draw();
			return;
		}
		m_RenderQueue.push_back(renderable);
	}

	void NRenderer::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			NRenderable* renderable = m_RenderQueue.front();
			NShader* shader = renderable->Shader;
			shader->Enable();
			shader->SetUniformMat4("view", NEngine::Camera->GetViewMatrix());
			shader->SetUniformMat4("projection", NEngine::Camera->GetProjectionMatrix());
			renderable->Draw();
			m_RenderQueue.pop_front();
		}
	}
}