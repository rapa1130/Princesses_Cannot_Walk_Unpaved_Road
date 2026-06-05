#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Renderer/Color.h"

namespace Bisang
{

	class LineRenderer: public RenderableComponent
	{
	public:
		LineRenderer(GameObject* ownerObj, Scene* scene);
		virtual void DrawCall(Renderer* renderer) override;

		void SetStartPosition(const Vector2& startPos) { m_startPos = startPos; }
		void SetEndPosition(const Vector2& endPos) { m_endPos = endPos; }
		void SetColor(const Bisang::Color& color) { m_color = color; }
		void SetLineWidth(float thickness) { m_thickness = thickness; }

		Vector2 GetStartPos() const { return m_startPos; }
		Vector2 GetEndPos() const { return m_endPos; }
		Bisang::Color GetColor() const { return m_color; }
		float GetLienWidth() const { return m_thickness; }

	protected:
		Vector2 m_startPos;
		Vector2 m_endPos;
		Bisang::Color m_color;
		float m_thickness;

	};
}