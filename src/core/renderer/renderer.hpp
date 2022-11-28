#pragma once
#include <deque>
#include "renderable.hpp"

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
				renderable->Draw();
				m_RenderQueue.pop_front();
			}
		}
	};
}