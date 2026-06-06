#include"Engine/Components/LineRenderer.h"
#include"Engine/Renderer/Color.h"
#include"Engine/Renderer/Renderer.h"

namespace Bisang
{
	LineRenderer::LineRenderer(GameObject* ownerObj, Scene* scene)
		:RenderableComponent(ownerObj,scene)
	{
		m_color = Bisang::Color::Red;
		m_thickness = 1.0f;
	}

	void LineRenderer::DrawCall(Renderer* renderer)
	{
		RenderCommand rc = RenderCommand::CreateLineRC(
			m_startPos,
			m_endPos,
			m_color,
			GetOrderInLayer(),
			m_thickness
		);

		renderer->Submit(rc);
	}
}