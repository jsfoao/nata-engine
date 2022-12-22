#pragma once
#include "nata.h"

namespace Nata
{
	class NWindow;
	class CModelRenderer : public CComponent, public NRenderable
	{
		GENERATE_COMPONENT;
	public:
		vec3 LocalRotation;
		vec3 LocalScale;
		vec3 LocalPosition;
		NPropertyBlockLayout PropertyLayout;

	protected:
		NRenderable* m_Renderable;
		bool m_IsVisible;

	public:
		CModelRenderer();
		inline void SetVisibility(bool visibility) { m_IsVisible = visibility; }
		inline NRenderable* GetRenderable() { return m_Renderable; }
		inline void SetRenderable(NRenderable* renderable) { m_Renderable = renderable; }
		void SetRenderableAndShader(NRenderable* renderable, NShader* shader);
		
		void Tick(float dt) override;
		void Draw() override;
	};
}