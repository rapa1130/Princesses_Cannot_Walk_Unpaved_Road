#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Renderer/Color.h"
#include"Engine/Math/Vector.h"

namespace Bisang
{

	class LineRenderer: public RenderableComponent
	{
	public:
		LineRenderer(GameObject* ownerObj);
		virtual void DrawCall(Renderer* renderer) override;

		void SetStartPosition(const Vector3& startPos) { m_startPos = startPos; }
		void SetEndPosition(const Vector3& endPos) { m_endPos = endPos; }
		void SetColor(const Bisang::Color& color) { m_color = color; }
		void SetLineWidth(float thickness) { m_thickness = thickness; }

		Vector3 GetStartPos() const { return m_startPos; }
		Vector3  GetEndPos() const { return m_endPos; }
		Bisang::Color GetColor() const { return m_color; }
		float GetLienWidth() const { return m_thickness; }

	protected:
		Vector3 m_startPos;
		Vector3 m_endPos;
		Bisang::Color m_color;
		float m_thickness = 1.0f;

	};
}