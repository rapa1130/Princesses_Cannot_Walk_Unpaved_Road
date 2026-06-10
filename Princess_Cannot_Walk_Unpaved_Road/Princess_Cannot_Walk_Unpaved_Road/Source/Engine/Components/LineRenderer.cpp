#include "Engine/Components/LineRenderer.h"
#include "Engine/Renderer/Color.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	LineRenderer::LineRenderer(GameObject* ownerObj)
		:RenderableComponent(ownerObj)
	{
		m_color = Bisang::Color::Red;
		m_thickness = 1.0f;
	}

	void LineRenderer::DrawCall(Renderer* renderer)
	{
		RenderCommand rc = RenderCommand::CreateLineRC(
			GetLayer(),
			m_transform->GetPosition(),
			m_startPos,
			m_endPos,
			m_thickness,
			m_color
		);

		renderer->Submit(rc);
	}
}