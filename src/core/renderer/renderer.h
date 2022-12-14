#pragma once
#include <deque>
#include "renderable.h"
#include "core/renderer/shader.h"
#include "core/ecs/CCamera.hpp"

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