#pragma once
#include <deque>
#include "renderable.hpp"
#include "core/ecs/CCamera.hpp"

namespace Nata
{
	class NRenderable;

	class NRenderer
	{
	private:
		std::deque<NRenderable*> m_RenderQueue;

	public:
		void Submit(NRenderable* renderable)
		{
			m_RenderQueue.push_back(renderable);
		}

		void Flush()
		{
			while (!m_RenderQueue.empty())
			{
				NRenderable* renderable = m_RenderQueue.front();
				NShader* shader = renderable->Shader;
				shader->Enable();
				shader->SetUniformMat4("view", NEngine::ActiveCamera->GetViewMatrix());
				shader->SetUniformMat4("projection", NEngine::ActiveCamera->GetProjectionMatrix());
				renderable->Draw();
				m_RenderQueue.pop_front();
			}
		}
	};
}