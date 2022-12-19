#pragma once
#include "nata.h"

namespace Nata
{
	class NWindow;
	class CModelRenderer : public CComponent
	{
		GENERATE_COMPONENT;
	protected:
		NShader* m_Shader;
		NTexture* m_Texture;
		NModel* m_Model;
		bool m_IsVisible;

	public:
		CModelRenderer();
		void Init(NShader* shader, NModel* model, NTexture* texture = nullptr);
		inline void SetVisibility(bool visibility) { m_IsVisible = visibility; }
		inline NShader* GetShader() { return m_Shader; }
		
		void Tick(float dt) override;
	};
}