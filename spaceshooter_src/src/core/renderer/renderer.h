#pragma once
#include <deque>
#include "renderable.h"
#include "core/renderer/shader.h"
#include "core/comp/CCamera.h"

namespace Nata
{
	class NRenderer
	{
	private:
		std::deque<NRenderable*> m_RenderQueue;

	public:
		void Submit(NRenderable* renderable, bool flush = false);
		void Flush();
	};
}